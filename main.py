import tkinter as tk
from frontEnd.startApp import ConnectFour

if __name__ == "__main__":
    root = tk.Tk()
    game = ConnectFour(root)
    root.mainloop()