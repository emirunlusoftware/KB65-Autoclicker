import tkinter as tk

counted_clicks = 0
counted_presses = 0



def click_counter(event=None):
    global counted_clicks
    counted_clicks += 1



def press_counter(event=None):
    global counted_presses
    counted_presses += 1



def show_click_and_press_times():
    global counted_clicks, counted_presses

    label_test.config(text=f"{counted_clicks} clicks / {counted_presses} presses per second!")
    print(f"{counted_clicks} clicks / {counted_presses} presses per second!")

    counted_clicks = 0
    counted_presses = 0

    window.after(1000, show_click_and_press_times)



def increase_font_size():
    label_click.config(font=("", int(label_click.cget("font").split()[1]) + 4))
    label_press.config(font=("", int(label_press.cget("font").split()[1]) + 4))
    label_test.config(font=("", int(label_test.cget("font").split()[1]) + 4, "bold"))
    label_change_size.config(font=("", int(label_change_size.cget("font").split()[1]) + 4))

    btn_bigfont.config(font=("", int(btn_bigfont.cget("font").split()[1]) + 4, "bold"))
    btn_smallfont.config(font=("", int(btn_smallfont.cget("font").split()[1]) + 4, "bold"))



def decrease_font_size():
    if int(btn_bigfont.cget("font").split()[1]) > 8:
        label_click.config(font=("", int(label_click.cget("font").split()[1]) - 4))
        label_press.config(font=("", int(label_press.cget("font").split()[1]) - 4))
        label_test.config(font=("", int(label_test.cget("font").split()[1]) - 4, "bold"))
        label_change_size.config(font=("", int(label_change_size.cget("font").split()[1]) - 4))

        btn_bigfont.config(font=("", int(btn_bigfont.cget("font").split()[1]) - 4, "bold"))
        btn_smallfont.config(font=("", int(btn_smallfont.cget("font").split()[1]) - 4, "bold"))



window = tk.Tk()
window.title("KB65 Autoclicker SpeedTest")
window.resizable(False, False)

window.bind("<Button-1>", click_counter)
window.bind("<Button-2>", click_counter)
window.bind("<Button-3>", click_counter)
window.bind("<Key>", press_counter)

label_click = tk.Label(window, text="Click here to test the clicker", font=("", 20))
label_press = tk.Label(window, text="Press any key to test the presser", font=("", 20))
label_test = tk.Label(window, text="0 clicks / 0 presses per second!", font=("", 16, "bold"), relief="raised")

label_click.pack(padx=10, pady=5)
label_press.pack(padx=10, pady=0)
label_test.pack(padx=10, pady=25)


frame = tk.Frame(window)
frame.pack(anchor = "center", padx=5, pady=5)

label_change_size= tk.Label(frame, text="Change Size", font=("", 12))
btn_bigfont = tk.Button(frame, text="+", command=increase_font_size, font=("", 12, "bold"), width=1, height=1, padx=1, pady=1)
btn_smallfont = tk.Button(frame, text="-", command=decrease_font_size, font=("", 12, "bold"), width=1, height=1, padx=1, pady=1)

label_change_size.grid(row=0, column=0, padx=1)
btn_bigfont.grid(row=0, column=1, padx=1)
btn_smallfont.grid(row=0, column=2, padx=1)


window.after(1000, show_click_and_press_times)
window.mainloop()
