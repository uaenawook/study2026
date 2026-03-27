import tkinter as tk
from tkinter import ttk, messagebox, simpledialog, colorchooser
import tkinter.font as tkfont
import time
import threading

# ── 修复#4：跨平台声音，非Windows不崩溃 ──────────────────────
try:
    import winsound
    _HAS_WINSOUND = True
except ImportError:
    _HAS_WINSOUND = False

from datetime import datetime, timedelta
from PIL import Image, ImageDraw, ImageFont
import pystray
from pystray import MenuItem as item
import os
import sys
import json
import math
import random
import re
from collections import Counter

class IU_UltimateManager:
    def __init__(self, root):
        self.root = root
        self.app_version = "0.27v"
        self.root.title(f"王总专用时间管理系统 - IU 终极完整版 {self.app_version}")
        
        self.scale_factor = getattr(self.root, 'scale_factor', 1.0)
        win_width = int(1100 * self.scale_factor)
        win_height = int(850 * self.scale_factor)
        self.root.geometry(f"{win_width}x{win_height}")
        self.root.configure(bg="#f0f2f5")
    
        self.root.protocol('WM_DELETE_WINDOW', self.hide_window)
        self.set_window_icon()
    
        self.data_file = os.path.join(os.getcwd(), "iu_data.json")
    
        self.active_alarms = [] 
        self.tasks = [] 
        self.task_cb_vars = {} 
        self.motto = "千里之行，始于足下。王总，今日事今日毕！" 
        
        self.motto_color = "#e67e22"
        self.ui_font = "微软雅黑"
        self.big_font = "Consolas"
        self.current_page = "闹钟"
        
        # 新增预设数据
        self.alarm_presets = [25, 45, 60, 120]
        self.task_presets = ["编程学习", "英语学习", "多邻国打卡", "Gitee维护", "QQ音乐签到"]
    
        self.sound_presets = {
            "清晨节奏": [(440, 200), (554, 200), (659, 200)],
            "紧急督促": [(1000, 150), (0, 50), (1000, 150)],
            "深度警报": [(1500, 300), (800, 300)],
            "轻柔微风": [(330, 300), (392, 300), (440, 400)],
            "短促提醒": [(800, 100), (0, 100), (800, 100)],
            "高频聚焦": [(2000, 200), (2500, 200)],
            "破晓之光": [(523, 200), (659, 200), (784, 400)],
            "稳重长鸣": [(400, 600), (0, 200), (400, 600)],
            "急促脉冲": [(1200, 50), (0, 50), (1200, 50), (0, 50), (1200, 50)]
        }
        self.selected_sound = tk.StringVar(value="清晨节奏")
        self.keep_ringing = tk.BooleanVar(value=True)
    
        # ── 番茄钟运行时状态（不持久化，每次启动重置）──────────
        self.pomo_state = "idle"          # idle | work | break | long_break | paused
        self._pomo_before_pause = "work"
        self.pomo_remaining = 0
        self.pomo_cycles = 0
        self.pomo_sessions = 0
        self.pomo_work_min = 25
        self.pomo_break_min = 5
        self.pomo_long_min = 15
        self._pomo_after_id = None
        self.stats_selected_date = time.strftime("%Y-%m-%d")
    
        self.load_data()
        self.pomo_remaining = self.pomo_work_min * 60
        self.BIG_FONT = (self.big_font, 60, "bold")
    
        self.init_styles()
        self.setup_ui()
        self.show_page("闹钟") 
        self.create_tray_icon()
        self.start_global_monitor()
    
    def init_styles(self):
        style = ttk.Style()
        style.configure('White.TRadiobutton', background='white', font=(self.ui_font, 10), indicatorsize=int(18 * self.scale_factor))
        style.map('White.TRadiobutton', background=[('active', 'white')])
        
        style.configure('Red.TCheckbutton', background='white', foreground='red', font=(self.ui_font, 9), indicatorsize=int(18 * self.scale_factor))
        style.map('Red.TCheckbutton', background=[('active', 'white')])
    
        style.configure('Task.TCheckbutton', background='#f8f9fa', foreground='#2c3e50', font=(self.ui_font, 12), indicatorsize=int(22 * self.scale_factor))
        style.map('Task.TCheckbutton', background=[('active', '#f8f9fa')])
        
        style.configure('TaskDone.TCheckbutton', background='#f8f9fa', foreground='#95a5a6', font=(self.ui_font, 12, "overstrike"), indicatorsize=int(22 * self.scale_factor))
        style.map('TaskDone.TCheckbutton', background=[('active', '#f8f9fa')])
    
    def set_window_icon(self):
        try:
            if hasattr(sys, '_MEIPASS'):
                icon_path = os.path.join(sys._MEIPASS, "logo.ico")
            else:
                icon_path = "logo.ico"
            self.root.iconbitmap(default=icon_path)
        except Exception:
            pass 
    
    def load_data(self):
        if os.path.exists(self.data_file):
            try:
                with open(self.data_file, "r", encoding="utf-8") as f:
                    data = json.load(f)
                    self.active_alarms = data.get("alarms", [])
                    self.tasks = data.get("tasks", [])
                    self.motto = data.get("motto", self.motto)
                    self.motto_color = data.get("motto_color", self.motto_color)
                    self.ui_font = data.get("ui_font", self.ui_font)
                    self.big_font = data.get("big_font", self.big_font)
                    self.alarm_presets = data.get("alarm_presets", self.alarm_presets)
                    self.task_presets = data.get("task_presets", self.task_presets)
                    
                    today_str = time.strftime("%Y-%m-%d")
                    for t in self.tasks:
                        if 'date' not in t:
                            t['date'] = today_str
            except Exception as e:
                print(f"数据读取失败: {e}")
    
    def save_data(self):
        data = {
            "alarms": self.active_alarms,
            "tasks": self.tasks,
            "motto": self.motto,
            "motto_color": self.motto_color,
            "ui_font": self.ui_font,
            "big_font": self.big_font,
            "alarm_presets": self.alarm_presets,
            "task_presets": self.task_presets
        }
        try:
            with open(self.data_file, "w", encoding="utf-8") as f:
                json.dump(data, f, ensure_ascii=False, indent=4)
        except Exception as e:
            print(f"数据保存失败: {e}")
    
    def create_tray_icon(self):
        try:
            if hasattr(sys, '_MEIPASS'):
                icon_path = os.path.join(sys._MEIPASS, "logo.ico")
            else:
                icon_path = "logo.ico"
            image = Image.open(icon_path)
        except:
            image = Image.new('RGB', (64, 64), color=(26, 188, 156))
            draw = ImageDraw.Draw(image)
            try:
                font = ImageFont.truetype("arial.ttf", 36)
                draw.text((12, 10), "IU", fill="white", font=font)
            except:
                font = ImageFont.load_default()
                draw.text((25, 25), "IU", fill="white", font=font)
        
        menu = (
            item('显示主界面', self.show_window_from_tray, default=True), 
            item('彻底退出', self.request_quit)
        )
        self.tray_icon = pystray.Icon("IUTimeMaster", image, "IU 时间大师", menu)
        threading.Thread(target=self.tray_icon.run, daemon=True).start()
    
    def hide_window(self): self.root.withdraw()
    def show_window_from_tray(self, icon=None, item=None): self.root.after(0, self.show_window)
    def show_window(self): self.root.deiconify(); self.root.lift(); self.root.focus_force()
        
    def request_quit(self, icon=None, item=None):
        self.root.after(0, self.confirm_quit)
        
    def confirm_quit(self):
        if messagebox.askyesno("IU 严格确认", "王总，您确定今天的代码写完、英语口语练完了吗？确定要退出系统？"):
            self.save_data()
            self.tray_icon.stop()
            self.root.quit()
            os._exit(0)
    
    def setup_ui(self):
        sb_width = int(200 * self.scale_factor)
        self.sidebar = tk.Frame(self.root, bg="#2c3e50", width=sb_width)
        self.sidebar.pack(side=tk.LEFT, fill=tk.Y)
        self.sidebar.pack_propagate(False)
    
        tk.Label(self.sidebar, text="IU MASTER", fg="#1abc9c", bg="#2c3e50", 
                 font=("Arial", 20, "bold"), pady=40).pack()
    
        self.menu_btns = {}
        # ── 修改需求2：删除"统计"，新增"云图"菜单项 ─────────────
        for menu in ["闹钟", "番茄", "任务", "云图"]:
            btn = tk.Button(self.sidebar, text=menu, bg="#34495e", fg="white", font=(self.ui_font, 12),
                            relief=tk.FLAT, bd=0, pady=25, cursor="hand2",
                            command=lambda m=menu: self.show_page(m))
            btn.pack(fill=tk.X, pady=1)
            self.menu_btns[menu] = btn
    
        self.right_frame = tk.Frame(self.root, bg="#f0f2f5")
        self.right_frame.pack(side=tk.RIGHT, expand=True, fill=tk.BOTH)
    
        tb_height = int(50 * self.scale_factor)
        self.top_bar = tk.Frame(self.right_frame, bg="#ecf0f1", height=tb_height)
        self.top_bar.pack(side=tk.TOP, fill=tk.X)
        self.top_bar.pack_propagate(False)
    
        self.motto_var = tk.StringVar(value=self.motto)
        tk.Label(self.top_bar, text="💡", bg="#ecf0f1", font=("Segoe UI Emoji", 14)).pack(side=tk.LEFT, padx=(20, 5), pady=10)
        
        self.motto_label = tk.Label(self.top_bar, textvariable=self.motto_var, font=(self.ui_font, 12, "bold"), fg=self.motto_color, bg="#ecf0f1")
        self.motto_label.pack(side=tk.LEFT, pady=10)
        
        tk.Button(self.top_bar, text="⚙ 外观设置", bg="#bdc3c7", fg="#2c3e50", font=(self.ui_font, 9), bd=0, cursor="hand2", command=self.open_appearance_settings, padx=10).pack(side=tk.RIGHT, padx=20, pady=12)
        tk.Button(self.top_bar, text="✎ 修改座右铭", bg="#bdc3c7", fg="#2c3e50", font=(self.ui_font, 9), bd=0, cursor="hand2", command=self.edit_motto, padx=10).pack(side=tk.RIGHT, padx=5, pady=12)
    
        self.main_container = tk.Frame(self.right_frame, bg="white")
        self.main_container.pack(side=tk.TOP, expand=True, fill=tk.BOTH, padx=25, pady=25)
    
    def edit_motto(self):
        new_motto = simpledialog.askstring("专属座右铭", "王总，请在此输入鞭策您的座右铭：", initialvalue=self.motto)
        if new_motto is not None and new_motto.strip() != "":
            self.motto = new_motto.strip()
            self.motto_var.set(self.motto)
            self.save_data()
    
    def open_appearance_settings(self):
        set_win = tk.Toplevel(self.root)
        set_win.title("IU 外观设置")
        set_win.geometry(f"{int(380 * self.scale_factor)}x{int(350 * self.scale_factor)}")
        set_win.configure(bg="white")
        set_win.transient(self.root)
        set_win.grab_set()
    
        tk.Label(set_win, text="修改座右铭颜色:", bg="white", font=(self.ui_font, 11, "bold")).pack(pady=(15, 5))
        color_btn = tk.Button(set_win, text="点击选择颜色", bg=self.motto_color, fg="white", font=(self.ui_font, 10), width=15)
        color_btn.pack()
    
        def choose_color():
            color_code = colorchooser.askcolor(title="选择座右铭颜色", initialcolor=self.motto_color)[1]
            if color_code:
                self.motto_color = color_code
                color_btn.config(bg=color_code)
                self.motto_label.config(fg=color_code)
        
        color_btn.config(command=choose_color)
    
        ttk.Separator(set_win, orient='horizontal').pack(fill=tk.X, pady=15, padx=20)
    
        available_fonts = list(tkfont.families())
        common_fonts = ["微软雅黑", "黑体", "宋体", "楷体", "Arial", "Consolas", "Segoe UI"]
        display_fonts = [f for f in common_fonts if f in available_fonts] + available_fonts
    
        tk.Label(set_win, text="选择全局界面字体:", bg="white", font=(self.ui_font, 11, "bold")).pack(pady=5)
        font_var = tk.StringVar(value=self.ui_font)
        font_cb = ttk.Combobox(set_win, textvariable=font_var, values=display_fonts, state="readonly", width=25)
        font_cb.pack()
    
        tk.Label(set_win, text="选择大号数字字体:", bg="white", font=(self.ui_font, 11, "bold")).pack(pady=(15, 5))
        big_font_var = tk.StringVar(value=self.big_font)
        big_font_cb = ttk.Combobox(set_win, textvariable=big_font_var, values=display_fonts, state="readonly", width=25)
        big_font_cb.pack()
    
        def save_settings():
            self.ui_font = font_var.get()
            self.big_font = big_font_var.get()
            self.BIG_FONT = (self.big_font, 60, "bold")
            
            self.init_styles() 
            for name, btn in self.menu_btns.items():
                btn.config(font=(self.ui_font, 12))
            self.motto_label.config(font=(self.ui_font, 12, "bold"))
            
            self.save_data()
            set_win.destroy()
            self.show_page(self.current_page) 
            messagebox.showinfo("IU 提示", "王总，字体与外观设置已生效！")
    
        tk.Button(set_win, text="✔ 保存设置", bg="#1abc9c", fg="white", font=(self.ui_font, 11, "bold"), width=20, command=save_settings).pack(pady=25)
    
    def show_page(self, name):
        self.current_page = name
        for n, btn in self.menu_btns.items():
            btn.config(bg="#1abc9c" if n == name else "#34495e")
        for widget in self.main_container.winfo_children(): widget.destroy()
    
        if name == "闹钟": self.render_alarm_page()
        elif name == "任务": self.render_task_page()
        elif name == "番茄": self.render_pomodoro_page()
        elif name == "云图": self.render_wordcloud_page()
    
    # ================= 任务列表模块 =================
    def get_available_dates(self):
        dates = list(set([t.get('date', time.strftime("%Y-%m-%d")) for t in self.tasks]))
        today_str = time.strftime("%Y-%m-%d")
        if today_str not in dates: dates.append(today_str)
        dates.sort(reverse=True)
        return dates
    
    def render_task_page(self):
        filter_frame = tk.Frame(self.main_container, bg="white")
        filter_frame.pack(fill=tk.X, pady=5)
        
        tk.Label(filter_frame, text="📅 查看日期:", bg="white", font=(self.ui_font, 12, "bold")).pack(side=tk.LEFT)
        
        self.current_view_date = tk.StringVar(value=time.strftime("%Y-%m-%d"))
        self.date_cb = ttk.Combobox(filter_frame, textvariable=self.current_view_date, 
                                    values=self.get_available_dates(), state="readonly", width=12, font=(self.ui_font, 11))
        self.date_cb.pack(side=tk.LEFT, padx=10)
        self.date_cb.bind("<<ComboboxSelected>>", lambda e: self.refresh_task_list())
        
        tk.Button(filter_frame, text="回到今天", bg="#3498db", fg="white", font=(self.ui_font, 10), bd=0, padx=10,
                  command=self.go_to_today).pack(side=tk.LEFT, padx=5)
    
        ttk.Separator(self.main_container, orient='horizontal').pack(fill=tk.X, pady=10)
        
        # 预设按钮区域
        preset_frame = tk.Frame(self.main_container, bg="white")
        preset_frame.pack(fill=tk.X, pady=5)
        tk.Label(preset_frame, text="每日预设:", bg="white", font=(self.ui_font, 12, "bold")).pack(side=tk.LEFT)
        
        self.task_preset_btns_frame = tk.Frame(preset_frame, bg="white")
        self.task_preset_btns_frame.pack(side=tk.LEFT, padx=10)
        self.render_task_preset_btns()
    
        # 手动输入区域
        input_frame = tk.Frame(self.main_container, bg="white")
        input_frame.pack(fill=tk.X, pady=10)
        tk.Label(input_frame, text="添加任务:", bg="white", font=(self.ui_font, 12, "bold")).pack(side=tk.LEFT)
        self.task_entry = tk.Entry(input_frame, width=40, font=(self.ui_font, 12))
        self.task_entry.pack(side=tk.LEFT, padx=10)
        # 回车添加到当前查看的日期
        self.task_entry.bind("<Return>", lambda e: self.add_task())
        self.add_task_btn = tk.Button(input_frame, text="✚ 添加到此日", bg="#1abc9c", fg="white",
                                      font=(self.ui_font, 10), command=self.add_task)
        self.add_task_btn.pack(side=tk.LEFT)
    
        # 提示当前正在操作哪天
        self.task_hint_label = tk.Label(self.main_container, text="", bg="white",
                                        fg="#7f8c8d", font=(self.ui_font, 9))
        self.task_hint_label.pack(anchor="w", padx=5)

        self.task_list_frame = tk.Frame(self.main_container, bg="white")
        self.task_list_frame.pack(fill=tk.BOTH, expand=True, pady=15)
        self.refresh_task_list()
    
    def render_task_preset_btns(self):
        for w in self.task_preset_btns_frame.winfo_children(): w.destroy()
        for pt in self.task_presets:
            tk.Button(self.task_preset_btns_frame, text=pt, font=(self.ui_font, 9), bg="#e8f6f3", fg="#16a085", bd=1,
                      command=lambda t=pt: self.add_task_val(t)).pack(side=tk.LEFT, padx=3)
        tk.Button(self.task_preset_btns_frame, text="✎ 修改预设", font=(self.ui_font, 9), bg="#bdc3c7", fg="#2c3e50", bd=0,
                  command=self.edit_task_presets).pack(side=tk.LEFT, padx=10)
    
    def edit_task_presets(self):
        curr = ",".join(self.task_presets)
        res = simpledialog.askstring("修改任务预设", "王总，请输入新预设（用英文逗号分隔）：", initialvalue=curr)
        if res is not None:
            new_presets = [x.strip() for x in res.split(",") if x.strip()]
            if new_presets:
                self.task_presets = new_presets
                self.save_data()
                self.render_task_preset_btns()
    
    def add_task_val(self, text):
        self.task_entry.delete(0, tk.END)
        self.task_entry.insert(0, text)
        self.add_task()
    
    def go_to_today(self):
        self.current_view_date.set(time.strftime("%Y-%m-%d"))
        self.refresh_task_list()
    
    def add_task(self):
        task_text = self.task_entry.get().strip()
        if task_text:
            # 添加到当前查看的日期，而非强制今天
            target_date = self.current_view_date.get()
            new_task = {"id": time.time(), "text": task_text, "completed": False, "date": target_date}
            self.tasks.append(new_task)
            self.task_entry.delete(0, tk.END)
            self.save_data()
            self.date_cb['values'] = self.get_available_dates()
            self.refresh_task_list()
    
    def toggle_task(self, task_id):
        for t in self.tasks:
            if t['id'] == task_id:
                t['completed'] = not t['completed']
                break
        self.save_data()
        self.refresh_task_list()
    
    def delete_task(self, task_id):
        self.tasks = [t for t in self.tasks if t['id'] != task_id]
        self.save_data()
        self.date_cb['values'] = self.get_available_dates() 
        self.refresh_task_list()

    def edit_task(self, task):
        """弹窗编辑任务文字和日期"""
        edit_win = tk.Toplevel(self.root)
        edit_win.title("编辑任务")
        edit_win.geometry(f"{int(420 * self.scale_factor)}x{int(200 * self.scale_factor)}")
        edit_win.configure(bg="white")
        edit_win.transient(self.root)
        edit_win.grab_set()

        tk.Label(edit_win, text="任务内容:", bg="white", font=(self.ui_font, 11, "bold")).pack(pady=(18, 4))
        text_entry = tk.Entry(edit_win, width=38, font=(self.ui_font, 11))
        text_entry.insert(0, task['text'])
        text_entry.pack()
        text_entry.focus_set()
        text_entry.select_range(0, tk.END)

        date_f = tk.Frame(edit_win, bg="white"); date_f.pack(pady=8)
        tk.Label(date_f, text="所属日期:", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT, padx=5)
        date_var = tk.StringVar(value=task.get('date', time.strftime("%Y-%m-%d")))
        date_cb = ttk.Combobox(date_f, textvariable=date_var,
                               values=self.get_available_dates(), width=13, font=(self.ui_font, 10))
        date_cb.pack(side=tk.LEFT)

        def save_edit():
            new_text = text_entry.get().strip()
            if not new_text:
                messagebox.showwarning("提示", "任务内容不能为空！", parent=edit_win)
                return
            task['text'] = new_text
            task['date'] = date_var.get()
            self.save_data()
            self.date_cb['values'] = self.get_available_dates()
            self.refresh_task_list()
            edit_win.destroy()

        tk.Button(edit_win, text="✔ 保存", bg="#1abc9c", fg="white",
                  font=(self.ui_font, 11, "bold"), width=14, command=save_edit).pack(pady=10)
        text_entry.bind("<Return>", lambda e: save_edit())
    
    def refresh_task_list(self):
        for widget in self.task_list_frame.winfo_children(): widget.destroy()
        self.task_cb_vars.clear() 
        
        view_date = self.current_view_date.get()
        today_str = time.strftime("%Y-%m-%d")
        filtered_tasks = [t for t in self.tasks if t.get('date') == view_date]
        
        # 更新按钮文字和提示，告知当前操作的日期
        if hasattr(self, 'add_task_btn'):
            if view_date == today_str:
                self.add_task_btn.config(text="✚ 添加到今日")
            else:
                self.add_task_btn.config(text=f"✚ 添加到 {view_date}")
        if hasattr(self, 'task_hint_label'):
            self.task_hint_label.config(text=f"当前操作日期：{view_date}  （可通过上方下拉框切换日期后添加/编辑任务）")
        
        if not filtered_tasks:
            msg = "今日暂无任务，王总请即刻添加学习计划！" if view_date == today_str else f"{view_date} 无记录，可在上方输入框添加任务。"
            tk.Label(self.task_list_frame, text=msg, bg="white", fg="#7f8c8d", font=(self.ui_font, 12)).pack(pady=20)
            return
    
        for task in filtered_tasks:
            row = tk.Frame(self.task_list_frame, bg="#f8f9fa", pady=10, padx=15)
            row.pack(fill=tk.X, pady=4)
            
            is_done = task['completed']
            var = tk.BooleanVar(value=is_done)
            self.task_cb_vars[task['id']] = var 
            
            style_name = 'TaskDone.TCheckbutton' if is_done else 'Task.TCheckbutton'
            cb = ttk.Checkbutton(row, text=task['text'], variable=var, style=style_name, 
                                 command=lambda tid=task['id']: self.toggle_task(tid))
            cb.pack(side=tk.LEFT)
            
            tk.Button(row, text="删除", bg="#e74c3c", fg="white", bd=0, padx=10,
                      command=lambda tid=task['id']: self.delete_task(tid)).pack(side=tk.RIGHT)
            tk.Button(row, text="编辑", bg="#3498db", fg="white", bd=0, padx=10,
                      command=lambda t=task: self.edit_task(t)).pack(side=tk.RIGHT, padx=5)
    
    # ================= 闹钟模块 =================
    def render_alarm_page(self):
        self.clock_label = tk.Label(self.main_container, text="", font=self.BIG_FONT, fg="#2c3e50", bg="white")
        self.clock_label.pack(pady=20)
        self.update_live_clock()
    
        set_frame = tk.LabelFrame(self.main_container, text=" 设置提醒 ", bg="white", padx=20, pady=20)
        set_frame.pack(fill=tk.X, pady=10)
    
        tk.Label(set_frame, text="任务名称:", bg="white", font=(self.ui_font, 10)).grid(row=0, column=0, sticky="w")
        self.alarm_title = tk.Entry(set_frame, width=15); self.alarm_title.insert(0, "学习C++"); self.alarm_title.grid(row=0, column=1, padx=5)
    
        tk.Label(set_frame, text="时间:", bg="white", font=(self.ui_font, 10)).grid(row=0, column=2, padx=10)
        t_f = tk.Frame(set_frame, bg="white"); t_f.grid(row=0, column=3)
        self.h_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(24)], width=3); self.h_cb.set(time.strftime("%H"))
        self.m_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(60)], width=3); self.m_cb.set(time.strftime("%M"))
        self.s_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(60)], width=3); self.s_cb.set("00")
        self.h_cb.pack(side=tk.LEFT); tk.Label(t_f, text=":", bg="white").pack(side=tk.LEFT)
        self.m_cb.pack(side=tk.LEFT); tk.Label(t_f, text=":", bg="white").pack(side=tk.LEFT)
        self.s_cb.pack(side=tk.LEFT)
    
        # Row 1: 快捷预设按钮
        tk.Label(set_frame, text="快捷预设:", bg="white", font=(self.ui_font, 10)).grid(row=1, column=0, pady=(15, 5), sticky="w")
        self.alarm_preset_frame = tk.Frame(set_frame, bg="white")
        self.alarm_preset_frame.grid(row=1, column=1, columnspan=3, sticky="w", pady=(15, 5))
        self.render_alarm_preset_btns()
    
        # Row 2: 自定义快捷填入
        tk.Label(set_frame, text="快捷填入:", bg="white", font=(self.ui_font, 10)).grid(row=2, column=0, pady=(0, 15), sticky="w")
        q_f = tk.Frame(set_frame, bg="white")
        q_f.grid(row=2, column=1, columnspan=3, sticky="w", pady=(0, 15))
        self.quick_entry = tk.Entry(q_f, width=5)
        self.quick_entry.insert(0, "5")
        self.quick_entry.pack(side=tk.LEFT)
        tk.Label(q_f, text="分钟后", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT, padx=5)
        tk.Button(q_f, text="填入", command=self.calc_quick_alarm, font=(self.ui_font, 9)).pack(side=tk.LEFT)
    
        # Row 3: 响铃方式
        tk.Label(set_frame, text="响铃方式:", bg="white", font=(self.ui_font, 10)).grid(row=3, column=0, pady=5, sticky="w")
        ring_opts_f = tk.Frame(set_frame, bg="white"); ring_opts_f.grid(row=3, column=1, columnspan=3, sticky="w")
        ttk.Checkbutton(ring_opts_f, text="持续响铃", variable=self.keep_ringing, style='Red.TCheckbutton').pack(side=tk.LEFT)
        tk.Label(ring_opts_f, text="或次数:", bg="white", font=(self.ui_font, 9)).pack(side=tk.LEFT, padx=(10, 2))
        self.ring_count_entry = tk.Entry(ring_opts_f, width=4, font=(self.ui_font, 9))
        self.ring_count_entry.insert(0, "1")
        self.ring_count_entry.pack(side=tk.LEFT)
    
        # ── 修复#7：持续响铃与次数输入框互斥联动 ──────────────
        def _toggle_ring_mode(*_):
            if self.keep_ringing.get():
                self.ring_count_entry.config(state='disabled')
            else:
                self.ring_count_entry.config(state='normal')
        self.keep_ringing.trace_add('write', _toggle_ring_mode)
        _toggle_ring_mode()   # 初始化时同步一次
    
        sound_box = tk.Frame(self.main_container, bg="white")
        sound_box.pack(fill=tk.X, pady=5)
        tk.Label(sound_box, text="选择铃声:", font=(self.ui_font, 10, "bold"), bg="white").pack(side=tk.LEFT, pady=5)
        self.sound_cb = ttk.Combobox(sound_box, textvariable=self.selected_sound, values=list(self.sound_presets.keys()), state="readonly", width=15)
        self.sound_cb.pack(side=tk.LEFT, padx=10)
        tk.Button(sound_box, text="🔊 试听", command=self.preview_sound, font=(self.ui_font, 9)).pack(side=tk.LEFT)
    
        tk.Button(self.main_container, text="确认设置闹钟", bg="#1abc9c", fg="white", font=(self.ui_font, 12, "bold"), pady=8, command=self.save_alarm).pack(fill=tk.X, pady=10)
    
        # ── 修复#5：闹钟列表加滚动条 ──────────────────────────
        list_outer = tk.Frame(self.main_container, bg="white")
        list_outer.pack(fill=tk.BOTH, expand=True)
        list_canvas = tk.Canvas(list_outer, bg="white", highlightthickness=0)
        list_sb = tk.Scrollbar(list_outer, orient="vertical", command=list_canvas.yview)
        self.alarm_list_frame = tk.Frame(list_canvas, bg="white")
        self.alarm_list_frame.bind(
            "<Configure>",
            lambda e: list_canvas.configure(scrollregion=list_canvas.bbox("all"))
        )
        _win_id = list_canvas.create_window((0, 0), window=self.alarm_list_frame, anchor="nw")
        list_canvas.configure(yscrollcommand=list_sb.set)
        list_canvas.bind("<Configure>", lambda e: list_canvas.itemconfig(_win_id, width=e.width))
        list_canvas.bind("<Enter>", lambda e: list_canvas.bind_all(
            "<MouseWheel>", lambda ev: list_canvas.yview_scroll(int(-1*(ev.delta/120)), "units")))
        list_canvas.bind("<Leave>", lambda e: list_canvas.unbind_all("<MouseWheel>"))
        list_canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        list_sb.pack(side=tk.RIGHT, fill=tk.Y)
        self.render_alarm_list()
    
    def render_alarm_preset_btns(self):
        for w in self.alarm_preset_frame.winfo_children(): w.destroy()
        for mins in self.alarm_presets:
            tk.Button(self.alarm_preset_frame, text=f"{mins}分钟", font=(self.ui_font, 9), bg="#ecf0f1", bd=1,
                      command=lambda m=mins: self.calc_quick_alarm_val(m)).pack(side=tk.LEFT, padx=3)
        tk.Button(self.alarm_preset_frame, text="✎ 修改预设", font=(self.ui_font, 9), bg="#bdc3c7", fg="#2c3e50", bd=0, 
                  command=self.edit_alarm_presets).pack(side=tk.LEFT, padx=10)
    
    def edit_alarm_presets(self):
        curr = ",".join(map(str, self.alarm_presets))
        res = simpledialog.askstring("修改闹钟预设", "王总，请输入新预设分钟数（英文逗号分隔）：", initialvalue=curr)
        if res is not None:
            try:
                new_presets = [int(x.strip()) for x in res.split(",") if x.strip().isdigit()]
                if new_presets:
                    self.alarm_presets = new_presets
                    self.save_data()
                    self.render_alarm_preset_btns()
            except Exception:
                messagebox.showerror("IU 错误", "输入格式有误，请确保输入数字。")
    
    def calc_quick_alarm_val(self, mins):
        future = datetime.now() + timedelta(minutes=int(mins))
        self.h_cb.set(future.strftime("%H"))
        self.m_cb.set(future.strftime("%M"))
        self.s_cb.set(future.strftime("%S"))
    
    def calc_quick_alarm(self):
        try:
            mins = int(self.quick_entry.get())
            future = datetime.now() + timedelta(minutes=mins)
            self.h_cb.set(future.strftime("%H"))
            self.m_cb.set(future.strftime("%M"))
            self.s_cb.set(future.strftime("%S"))
        except ValueError:
            messagebox.showerror("IU 错误", "王总，请输入有效的分钟数！")
    
    def update_live_clock(self):
        if hasattr(self, 'clock_label'):
            self.clock_label.config(text=time.strftime("%H:%M:%S"))
            self.root.after(1000, self.update_live_clock)
    
    # ================= 辅助功能逻辑 =================
    def preview_sound(self):
        melody = self.sound_presets[self.selected_sound.get()]
        threading.Thread(target=self._play_sound_once, args=(melody,), daemon=True).start()
    
    def _play_sound_once(self, melody):
        # ── 修复#4：非Windows系统不崩溃 ─────────────────────
        for f, d in melody:
            if f == 0:
                time.sleep(d / 1000)
            elif _HAS_WINSOUND:
                winsound.Beep(f, d)
            else:
                time.sleep(d / 1000)
    
    def save_alarm(self):
        t = f"{self.h_cb.get()}:{self.m_cb.get()}:{self.s_cb.get()}"
        try:
            r_count = int(self.ring_count_entry.get())
        except:
            r_count = 1
            
        self.active_alarms.append({
            "id": time.time(), 
            "title": self.alarm_title.get(), 
            "time": t, 
            "sound": self.selected_sound.get(), 
            "continuous": self.keep_ringing.get(), 
            "ring_count": r_count,
            "active": True
        })
        self.save_data()
        self.render_alarm_list()
    
    def render_alarm_list(self):
        for w in self.alarm_list_frame.winfo_children(): w.destroy()
        for a in self.active_alarms:
            row = tk.Frame(self.alarm_list_frame, bg="#f8f9fa", pady=8, padx=15)
            row.pack(fill=tk.X, pady=3)
            
            status_text = "" if a['active'] else " (已失效)"
            font_col = "#2c3e50" if a['active'] else "#95a5a6"
            
            is_cont = a.get('continuous', False)
            rc = a.get('ring_count', 1)
            ring_str = "持续响铃" if is_cont else f"响{rc}次"
            display_str = f"{a['time']} [{ring_str}]{status_text}"
            
            tk.Label(row, text=f"{a['title']}", bg="#f8f9fa", fg=font_col, font=(self.ui_font, 11, "bold")).pack(side=tk.LEFT)
            tk.Label(row, text=display_str, bg="#f8f9fa", fg=font_col, font=(self.big_font, 11)).pack(side=tk.LEFT, padx=25)
            
            tk.Button(row, text="删除", bg="#e74c3c", fg="white", font=(self.ui_font, 9), bd=0, padx=15, 
                      command=lambda aid=a['id']: self.remove_alarm(aid)).pack(side=tk.RIGHT)
                      
            tk.Button(row, text="编辑", bg="#3498db", fg="white", font=(self.ui_font, 9), bd=0, padx=15, 
                      command=lambda a_dict=a: self.edit_alarm(a_dict)).pack(side=tk.RIGHT, padx=5)
    
            # ── 修复#3：失效闹钟显示"重新激活"按钮 ──────────
            if not a['active']:
                tk.Button(row, text="重新激活", bg="#27ae60", fg="white", font=(self.ui_font, 9), bd=0, padx=10,
                          command=lambda aid=a['id']: self.reactivate_alarm(aid)).pack(side=tk.RIGHT, padx=5)
    
    def reactivate_alarm(self, aid):
        """修复#3：将失效闹钟重置为激活"""
        for a in self.active_alarms:
            if a['id'] == aid:
                a['active'] = True
                break
        self.save_data()
        self.render_alarm_list()
    
    def edit_alarm(self, alarm):
        edit_win = tk.Toplevel(self.root)
        edit_win.title("IU - 修改闹钟")
        # ── 修复#2：窗口加高，容纳新增的标题/铃声字段 ─────────
        edit_win.geometry(f"{int(380 * self.scale_factor)}x{int(370 * self.scale_factor)}")
        edit_win.configure(bg="white")
        edit_win.transient(self.root)
        edit_win.grab_set()
    
        tk.Label(edit_win, text="编辑任务", bg="white", font=(self.ui_font, 12, "bold")).pack(pady=(15, 8))
    
        # ── 修复#2：新增任务名称编辑 ────────────────────────
        title_f = tk.Frame(edit_win, bg="white"); title_f.pack(pady=4)
        tk.Label(title_f, text="任务名称:", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT, padx=5)
        title_entry = tk.Entry(title_f, width=18, font=(self.ui_font, 10))
        title_entry.insert(0, alarm.get('title', ''))
        title_entry.pack(side=tk.LEFT, padx=5)
    
        t_f = tk.Frame(edit_win, bg="white"); t_f.pack(pady=4)
        tk.Label(t_f, text="时间:", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT, padx=5)
        h_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(24)], width=3)
        m_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(60)], width=3)
        s_cb = ttk.Combobox(t_f, values=[f"{i:02d}" for i in range(60)], width=3)
        h, m, s = alarm['time'].split(':')
        h_cb.set(h); m_cb.set(m); s_cb.set(s)
        h_cb.pack(side=tk.LEFT); tk.Label(t_f, text=":", bg="white").pack(side=tk.LEFT)
        m_cb.pack(side=tk.LEFT); tk.Label(t_f, text=":", bg="white").pack(side=tk.LEFT)
        s_cb.pack(side=tk.LEFT)
    
        # ── 修复#2：新增铃声编辑 ────────────────────────────
        sound_f = tk.Frame(edit_win, bg="white"); sound_f.pack(pady=4)
        tk.Label(sound_f, text="铃声:", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT, padx=5)
        sound_var = tk.StringVar(value=alarm.get('sound', '清晨节奏'))
        ttk.Combobox(sound_f, textvariable=sound_var,
                     values=list(self.sound_presets.keys()), state="readonly", width=14).pack(side=tk.LEFT, padx=5)
    
        c_f = tk.Frame(edit_win, bg="white"); c_f.pack(pady=10)
        cont_var = tk.BooleanVar(value=alarm.get('continuous', False))
        ttk.Checkbutton(c_f, text="持续响铃", variable=cont_var, style='Red.TCheckbutton').pack(side=tk.TOP, pady=5)
        
        rc_f = tk.Frame(c_f, bg="white"); rc_f.pack(side=tk.TOP)
        tk.Label(rc_f, text="或指定响铃次数:", bg="white", font=(self.ui_font, 10)).pack(side=tk.LEFT)
        rc_entry = tk.Entry(rc_f, width=5, font=(self.ui_font, 10))
        rc_entry.insert(0, str(alarm.get('ring_count', 1)))
        rc_entry.pack(side=tk.LEFT, padx=5)
    
        # ── 修复#7：编辑弹窗内同样互斥联动 ──────────────────
        def _toggle_edit(*_):
            rc_entry.config(state='disabled' if cont_var.get() else 'normal')
        cont_var.trace_add('write', _toggle_edit)
        _toggle_edit()
    
        def save_edit():
            new_title = title_entry.get().strip()
            if new_title:
                alarm['title'] = new_title
            alarm['time'] = f"{h_cb.get()}:{m_cb.get()}:{s_cb.get()}"
            alarm['sound'] = sound_var.get()
            alarm['continuous'] = cont_var.get()
            try:
                alarm['ring_count'] = int(rc_entry.get())
            except ValueError:
                alarm['ring_count'] = 1
            alarm['active'] = True 
            self.save_data()
            self.render_alarm_list()
            edit_win.destroy()
    
        tk.Button(edit_win, text="✔ 保存修改", bg="#1abc9c", fg="white", font=(self.ui_font, 11, "bold"), width=15, command=save_edit).pack(pady=10)
    
    def remove_alarm(self, aid):
        self.active_alarms = [a for a in self.active_alarms if a['id'] != aid]
        self.save_data()
        self.render_alarm_list()
    
    def start_global_monitor(self):
        # ── 修复#1：datetime窗口比对，彻底防止闹钟漏触发 ──────
        def monitor():
            while True:
                now_dt = datetime.now()
                for a in list(self.active_alarms):
                    if not a['active']:
                        continue
                    try:
                        alarm_dt = datetime.strptime(a['time'], "%H:%M:%S").replace(
                            year=now_dt.year, month=now_dt.month, day=now_dt.day)
                        diff = (now_dt - alarm_dt).total_seconds()
                        # 0~3秒窗口触发，sleep(0.5)轮询不会再漏
                        if 0 <= diff < 3:
                            a['active'] = False
                            self.root.after(0, self.save_data)
                            self.show_window_from_tray()
                            if self.current_page == "闹钟":
                                self.root.after(0, self.render_alarm_list)
                            threading.Thread(target=self._fire_alarm, args=(a,), daemon=True).start()
                    except Exception:
                        pass
                time.sleep(0.5)
        threading.Thread(target=monitor, daemon=True).start()
    
    def _fire_alarm(self, alarm):
        stop_flag = threading.Event()
        def ring():
            melody = self.sound_presets[alarm['sound']]
            is_cont = alarm.get('continuous', False)
            max_count = alarm.get('ring_count', 1)
            count = 0
            while not stop_flag.is_set():
                for f, d in melody:
                    if stop_flag.is_set(): break
                    if f == 0:
                        time.sleep(d / 1000)
                    elif _HAS_WINSOUND:   # ── 修复#4
                        winsound.Beep(f, d)
                    else:
                        time.sleep(d / 1000)
                count += 1
                if not is_cont and count >= max_count:
                    break
                if stop_flag.is_set(): break
                time.sleep(1)
        threading.Thread(target=ring, daemon=True).start()
        messagebox.showwarning("IU 提醒", f"王总，任务：【{alarm['title']}】时间到了！")
        stop_flag.set()
    
    # ================= 番茄钟模块 =================
    def render_pomodoro_page(self):
        tk.Label(self.main_container, text="🍅 番茄钟",
                 font=(self.ui_font, 18, "bold"), bg="white", fg="#2c3e50").pack(pady=(8, 2))
    
        self._pomo_state_lbl = tk.Label(self.main_container, text=self._pomo_state_text(),
                                         font=(self.ui_font, 12), fg="#e74c3c", bg="white")
        self._pomo_state_lbl.pack()
    
        self._pomo_canvas = tk.Canvas(self.main_container, width=420, height=420,
                                       bg="white", highlightthickness=0)
        self._pomo_canvas.pack(pady=10)
        self._pomo_draw()
    
        self._pomo_session_lbl = tk.Label(self.main_container,
                                           text=f"今日番茄: {self.pomo_sessions} 🍅",
                                           font=(self.ui_font, 11), fg="#7f8c8d", bg="white")
        self._pomo_session_lbl.pack()
    
        btn_f = tk.Frame(self.main_container, bg="white"); btn_f.pack(pady=12)
        self._pomo_toggle_btn = tk.Button(btn_f, text=self._pomo_btn_text(),
                                           font=(self.ui_font, 12, "bold"),
                                           bg="#e74c3c", fg="white", bd=0, padx=25, pady=8,
                                           cursor="hand2", command=self._pomo_toggle)
        self._pomo_toggle_btn.pack(side=tk.LEFT, padx=8)
        tk.Button(btn_f, text="↺ 重置", font=(self.ui_font, 11),
                  bg="#95a5a6", fg="white", bd=0, padx=15, pady=8,
                  cursor="hand2", command=self._pomo_reset).pack(side=tk.LEFT, padx=8)
    
        sound_f = tk.Frame(self.main_container, bg="white")
        sound_f.pack(pady=(0, 8))
        self._pomo_sound_lbl = tk.Label(sound_f,
                                        text=f"提示铃声：{self.selected_sound.get()}（专注结束 / 休息结束时使用）",
                                        font=(self.ui_font, 10), fg="#7f8c8d", bg="white")
        self._pomo_sound_lbl.pack(side=tk.LEFT)
        tk.Button(sound_f, text="🔊 试听", command=self.preview_sound,
                  font=(self.ui_font, 9), bd=0, bg="#ecf0f1", padx=10,
                  cursor="hand2").pack(side=tk.LEFT, padx=8)
    
        cfg_f = tk.LabelFrame(self.main_container, text=" 时长配置（分钟）",
                               bg="white", padx=20, pady=10)
        cfg_f.pack(fill=tk.X, pady=8, padx=20)
        for label, attr in [("🔴 专注", "pomo_work_min"),
                             ("🟡 短休息", "pomo_break_min"),
                             ("🔵 长休息", "pomo_long_min")]:
            fr = tk.Frame(cfg_f, bg="white"); fr.pack(side=tk.LEFT, padx=30)
            tk.Label(fr, text=label, font=(self.ui_font, 10), bg="white").pack()
            var = tk.IntVar(value=getattr(self, attr))
            ttk.Spinbox(fr, from_=1, to=180, textvariable=var, width=5).pack()
            def _mk(a, v):
                def _cb(*_):
                    try: setattr(self, a, int(v.get()))
                    except Exception: pass
                    if self.pomo_state == "idle":
                        self.pomo_remaining = self.pomo_work_min * 60
                        self._pomo_draw()
                return _cb
            var.trace_add("write", _mk(attr, var))
    
        note_f = tk.Frame(self.main_container, bg="white")
        note_f.pack(fill=tk.X, padx=20, pady=(2, 0))
        tk.Label(note_f,
                 text="短休息：每完成 1 次专注后休息；长休息：每完成 4 次专注后自动进入更长的休息。",
                 font=(self.ui_font, 9), fg="#95a5a6", bg="white").pack(anchor="w")
        tk.Label(note_f,
                 text="使用方式：点击[开始专注]后，流程会按[专注-短休息-专注]循环，每第 4 轮自动切换到长休息。",
                 font=(self.ui_font, 9), fg="#95a5a6", bg="white").pack(anchor="w", pady=(3, 0))
    
    def _pomo_state_text(self):
        return {"idle": "准备开始", "work": "🔴 专注中", "break": "🟢 休息中",
                "long_break": "🔵 长休息中", "paused": "⏸ 已暂停"}.get(self.pomo_state, "")
    
    def _pomo_btn_text(self):
        if self.pomo_state == "idle":   return "▶ 开始专注"
        if self.pomo_state == "paused": return "▶ 继续"
        return "⏸ 暂停"
    
    def _pomo_total_secs(self):
        if self.pomo_state in ("idle", "work", "paused"): return self.pomo_work_min * 60
        if self.pomo_state == "break":                     return self.pomo_break_min * 60
        if self.pomo_state == "long_break":                return self.pomo_long_min * 60
        return self.pomo_work_min * 60
    
    def _pomo_draw(self):
        if not hasattr(self, "_pomo_canvas") or not self._pomo_canvas.winfo_exists():
            return
        c = self._pomo_canvas; c.delete("all")
        cw = int(c.cget("width")); ch = int(c.cget("height"))
        cx = cw // 2; cy = ch // 2 + 2
        r = min(cw, ch) // 2 - 22
        ring_w = 18
        c.create_oval(cx-r, cy-r, cx+r, cy+r, outline="#ecf0f1", width=ring_w, fill="white")
    
        total = self._pomo_total_secs()
        if total and self.pomo_state != "idle":
            pct = 1 - self.pomo_remaining / total
            angle = pct * 359.9
            color = {"work": "#e74c3c", "break": "#2ecc71",
                     "long_break": "#3498db", "paused": "#f39c12"}.get(self.pomo_state, "#1abc9c")
            c.create_arc(cx-r, cy-r, cx+r, cy+r, start=90, extent=-angle,
                         outline=color, width=ring_w, style="arc")
    
        if self.pomo_state == "idle":
            m, s = self.pomo_work_min, 0
        else:
            m, s = divmod(self.pomo_remaining, 60)
    
        tcolor = {"idle": "#95a5a6", "work": "#e74c3c", "break": "#27ae60",
                  "long_break": "#2980b9", "paused": "#f39c12"}.get(self.pomo_state, "#2c3e50")
        c.create_text(cx, cy, text=f"{m:02d}:{s:02d}",
                      font=(self.big_font, 38, "bold"), fill=tcolor)
        sub = {"idle": "", "work": "保持专注", "break": "好好休息",
               "long_break": "充分放松", "paused": "暂停中"}.get(self.pomo_state, "")
        if sub:
            c.create_text(cx, cy+86, text=sub, font=(self.ui_font, 12), fill="#aaa")
    
    def _pomo_toggle(self):
        if self.pomo_state == "idle":
            self.pomo_state = "work"
            self.pomo_remaining = self.pomo_work_min * 60
            self._pomo_tick()
        elif self.pomo_state == "paused":
            self.pomo_state = self._pomo_before_pause
            self._pomo_tick()
        else:
            self._pomo_before_pause = self.pomo_state
            if self._pomo_after_id:
                self.root.after_cancel(self._pomo_after_id)
                self._pomo_after_id = None
            self.pomo_state = "paused"
        self._pomo_refresh_ui()
    
    def _pomo_reset(self):
        if self._pomo_after_id:
            self.root.after_cancel(self._pomo_after_id)
            self._pomo_after_id = None
        self.pomo_state = "idle"
        self.pomo_remaining = self.pomo_work_min * 60
        self._pomo_refresh_ui()
    
    def _pomo_tick(self):
        if self.pomo_state not in ("work", "break", "long_break"):
            return
        if self.pomo_remaining > 0:
            self.pomo_remaining -= 1
            self._pomo_draw()
            self._pomo_after_id = self.root.after(1000, self._pomo_tick)
        else:
            self._pomo_phase_done()
    
    def _pomo_phase_done(self):
        sound_name = self.selected_sound.get() if self.selected_sound.get() in self.sound_presets else "破晓之光"
        threading.Thread(target=self._play_sound_once,
                         args=(self.sound_presets[sound_name],), daemon=True).start()
        if self.pomo_state == "work":
            self.pomo_sessions += 1
            self.pomo_cycles += 1
            if hasattr(self, "_pomo_session_lbl") and self._pomo_session_lbl.winfo_exists():
                self._pomo_session_lbl.config(text=f"今日番茄: {self.pomo_sessions} 🍅")
            if self.pomo_cycles % 4 == 0:
                self.pomo_state = "long_break"
                self.pomo_remaining = self.pomo_long_min * 60
                messagebox.showinfo("番茄钟 🎉",
                    f"完成 {self.pomo_cycles} 个番茄！\n享受 {self.pomo_long_min} 分钟长休息~")
            else:
                self.pomo_state = "break"
                self.pomo_remaining = self.pomo_break_min * 60
                messagebox.showinfo("番茄钟 ✅",
                    f"专注完成！休息 {self.pomo_break_min} 分钟~")
        else:
            self.pomo_state = "work"
            self.pomo_remaining = self.pomo_work_min * 60
            messagebox.showinfo("番茄钟 💪", "休息结束，继续专注！")
        self._pomo_refresh_ui()
        self._pomo_tick()
    
    def _pomo_refresh_ui(self):
        self._pomo_draw()
        if hasattr(self, "_pomo_state_lbl") and self._pomo_state_lbl.winfo_exists():
            self._pomo_state_lbl.config(text=self._pomo_state_text())
        if hasattr(self, "_pomo_toggle_btn") and self._pomo_toggle_btn.winfo_exists():
            self._pomo_toggle_btn.config(text=self._pomo_btn_text())
        if hasattr(self, "_pomo_sound_lbl") and self._pomo_sound_lbl.winfo_exists():
            self._pomo_sound_lbl.config(text=f"提示铃声：{self.selected_sound.get()}（专注结束 / 休息结束时使用）")
    
    def _get_weekday_text(self, date_str):
        try:
            return ["周一", "周二", "周三", "周四", "周五", "周六", "周日"][datetime.strptime(date_str, "%Y-%m-%d").weekday()]
        except Exception:
            return ""
    
    # ================= 云图模块（新增） =================
    def _get_word_freq(self):
        """从所有任务文本提取词频：只按标点/空格分割，整段作为词，不再滑窗拆字"""
        all_texts = [t.get('text', '') for t in self.tasks]
        word_counts = Counter()
        # 分割符号：中英文标点、空格
        split_pattern = r'[、，。；：！？,\.;:!\?\s\-\|/\\+&《》【】（）()""\'\'「」]+'
        for text in all_texts:
            segments = re.split(split_pattern, text.strip())
            for seg in segments:
                seg = seg.strip()
                if len(seg) >= 1:   # 保留所有切割后的片段（包括单字）
                    word_counts[seg] += 1
        return word_counts

    def _calc_streak(self):
        today = datetime.now().date(); streak = 0
        for i in range(365):
            ds = (today - timedelta(days=i)).strftime("%Y-%m-%d")
            if any(t.get('date') == ds for t in self.tasks):
                streak += 1
            elif i > 0:
                break
        return streak

    def _calc_checkin_days(self):
        """统计有任务记录的总天数（签到天数）"""
        return len(set(t.get('date', '') for t in self.tasks if t.get('date')))

    def render_wordcloud_page(self):
        # ── 顶部标题行 ──────────────────────────────────────
        title_bar = tk.Frame(self.main_container, bg="white")
        title_bar.pack(fill=tk.X, pady=(0, 5))
        tk.Label(title_bar, text="☁ 任务云图", font=(self.ui_font, 18, "bold"),
                 bg="white", fg="#2c3e50").pack(side=tk.LEFT)
        tk.Button(title_bar, text="🔄 刷新云图", bg="#1abc9c", fg="white",
                  font=(self.ui_font, 10), bd=0, padx=12, cursor="hand2",
                  command=lambda: self.show_page("云图")).pack(side=tk.RIGHT)

        # ── 统计卡片行 ──────────────────────────────────────
        today_str = time.strftime("%Y-%m-%d")
        today_tasks = [t for t in self.tasks if t.get('date') == today_str]
        today_done = sum(1 for t in today_tasks if t['completed'])
        total_tasks = len(self.tasks)
        total_done = sum(1 for t in self.tasks if t['completed'])
        streak = self._calc_streak()
        checkin_days = self._calc_checkin_days()
        completion_rate = int(total_done / total_tasks * 100) if total_tasks else 0

        cards_f = tk.Frame(self.main_container, bg="white")
        cards_f.pack(fill=tk.X, pady=(0, 6))
        cards_data = [
            ("📅 签到天数", f"{checkin_days} 天",   "#3498db"),
            ("🔥 连续打卡", f"{streak} 天",         "#e74c3c"),
            ("✅ 今日完成", f"{today_done}/{len(today_tasks)}", "#1abc9c"),
            ("📊 累计完成率", f"{completion_rate}%", "#9b59b6"),
            ("📝 总任务数",  f"{total_tasks} 条",   "#e67e22"),
        ]
        for label, val, color in cards_data:
            card = tk.Frame(cards_f, bg=color, padx=10, pady=8)
            card.pack(side=tk.LEFT, padx=4, expand=True, fill=tk.X)
            tk.Label(card, text=val,   font=(self.ui_font, 14, "bold"), fg="white", bg=color).pack()
            tk.Label(card, text=label, font=(self.ui_font, 8),          fg="white", bg=color).pack()

        ttk.Separator(self.main_container, orient='horizontal').pack(fill=tk.X, pady=3)

        word_counts = self._get_word_freq()

        if not word_counts:
            tk.Label(self.main_container, text="暂无任务数据，请先在任务页面添加任务！",
                     bg="white", fg="#7f8c8d", font=(self.ui_font, 14)).pack(expand=True)
            return

        # ── 词云 Canvas：占据大部分剩余空间 ─────────────────
        cloud_outer = tk.Frame(self.main_container, bg="white")
        cloud_outer.pack(fill=tk.BOTH, expand=True)

        self._wc_canvas = tk.Canvas(cloud_outer, bg="#f0f4f8", highlightthickness=1,
                                    highlightbackground="#dde3ec")
        self._wc_canvas.pack(fill=tk.BOTH, expand=True, padx=4, pady=4)

        # ── 底部词频排行（紧凑一行横排）──────────────────────
        rank_frame = tk.Frame(self.main_container, bg="#f8f9fa")
        rank_frame.pack(fill=tk.X, padx=4, pady=(0, 2))
        tk.Label(rank_frame, text="Top 10：", bg="#f8f9fa",
                 font=(self.ui_font, 9, "bold"), fg="#2c3e50").pack(side=tk.LEFT, padx=6)
        bar_colors = ["#e74c3c","#e67e22","#f1c40f","#27ae60","#1abc9c",
                      "#3498db","#9b59b6","#e91e63","#00bcd4","#ff5722"]
        top10 = word_counts.most_common(10)
        for i, (word, cnt) in enumerate(top10):
            lbl = tk.Label(rank_frame, text=f"{word}({cnt})",
                           bg=bar_colors[i % len(bar_colors)], fg="white",
                           font=(self.ui_font, 9), padx=6, pady=2)
            lbl.pack(side=tk.LEFT, padx=2, pady=3)

        # 绑定 Configure：canvas 第一次获得真实尺寸时自动触发绘制
        self._wc_word_counts = word_counts
        self._wc_canvas.bind("<Configure>", self._on_wc_resize)

    def _on_wc_resize(self, event):
        """Canvas 尺寸变化时防抖重绘"""
        if hasattr(self, '_wc_resize_job'):
            self.root.after_cancel(self._wc_resize_job)
        self._wc_resize_job = self.root.after(
            200, lambda: self._draw_wordcloud(self._wc_word_counts)
        )

    def _draw_wordcloud(self, word_counts):
        """普通词云：Top3彩色其余灰色，精确行高碰撞，绝不叠字"""
        if not hasattr(self, '_wc_canvas') or not self._wc_canvas.winfo_exists():
            return
        c = self._wc_canvas
        c.update_idletasks()
        W = c.winfo_width()
        H = c.winfo_height()
        if W < 80 or H < 80:
            self.root.after(200, lambda: self._draw_wordcloud(word_counts))
            return

        c.delete("all")
        c.create_rectangle(0, 0, W, H, fill="#f7f9fc", outline="")

        top_n = min(max(15, W * H // 3000), 80, len(word_counts))
        top_words = word_counts.most_common(top_n)
        if not top_words:
            return

        max_freq = top_words[0][1]
        min_freq = top_words[-1][1]

        # Top3 高亮色，其余灰色梯度
        top3_colors = ["#e74c3c", "#e67e22", "#3498db"]
        gray_shades = ["#888888", "#919191", "#9a9a9a", "#a2a2a2",
                       "#aaaaaa", "#b2b2b2", "#bbbbbb", "#c3c3c3"]

        placed = []   # list of (x1, y1, x2, y2)

        def no_overlap(r):
            PAD = 10   # 安全间距，中文字符需要更大
            for p in placed:
                if not (r[2] + PAD <= p[0] or p[2] + PAD <= r[0] or
                        r[3] + PAD <= p[1] or p[3] + PAD <= r[1]):
                    return False
            return True

        cx0, cy0 = W // 2, H // 2

        def try_place(word, font_size):
            # 用 tkfont.metrics 精确获取行高
            fo      = tkfont.Font(family=self.ui_font, size=font_size, weight="bold")
            tw      = fo.measure(word)
            metrics = fo.metrics()
            th      = metrics["ascent"] + metrics["descent"]
            hw = tw // 2 + 8   # 横向边距 8px
            hh = th // 2 + 6   # 纵向边距 6px

            a       = 0.0
            dr      = 0.0
            da      = 0.12                              # 角步长（越小越密）
            dr_step = (th + 12) / (2 * math.pi) * da   # 每弧度推进距离
            max_r   = math.sqrt((W / 2) ** 2 + (H / 2) ** 2) * 1.15

            while dr < max_r:
                x = int(cx0 + dr * math.cos(a))
                y = int(cy0 + dr * math.sin(a) * 0.65)
                x = max(hw + 2, min(W - hw - 2, x))
                y = max(hh + 2, min(H - hh - 2, y))
                rect = (x - hw, y - hh, x + hw, y + hh)
                if no_overlap(rect):
                    placed.append(rect)
                    return x, y
                a  += da
                dr += dr_step
            return None

        random.seed(42)
        gray_idx = 0

        for rank, (word, freq) in enumerate(top_words):
            if max_freq == min_freq:
                font_size = 22
            else:
                t = (freq - min_freq) / (max_freq - min_freq)
                font_size = int(10 + t * 28)
            font_size = max(10, min(38, font_size))

            if rank < 3:
                color = top3_colors[rank]
            else:
                color = gray_shades[gray_idx % len(gray_shades)]
                gray_idx += 1

            pos = try_place(word, font_size)
            if pos:
                x, y = pos
                c.create_text(x, y, text=word,
                              font=(self.ui_font, font_size, "bold"),
                              fill=color, anchor="center")

        placed_cnt = len(placed)
        c.create_text(W - 6, H - 6,
                      text=f"共 {len(word_counts)} 个词  已显示 {placed_cnt}",
                      font=(self.ui_font, 8), fill="#c0c8d4", anchor="se")


if __name__ == "__main__":
    sys_scale = 1.0
    try:
        import ctypes
        ctypes.windll.shcore.SetProcessDpiAwareness(1)
        sys_scale = ctypes.windll.user32.GetDpiForSystem() / 96.0
    except Exception:
        sys_scale = 1.0

    root = tk.Tk()
    root.scale_factor = sys_scale
    
    style = ttk.Style()
    style.theme_use('clam')
    app = IU_UltimateManager(root)
    root.mainloop()
