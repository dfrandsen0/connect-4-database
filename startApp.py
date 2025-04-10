import tkinter as tk
from tkinter import messagebox

import time, random

ROWS = 6
COLS = 7
CELL_SIZE = 80

class ConnectFour:
    def __init__(self, root):
        self.root = root
        self.root.title("Connect Four")

        self.ai_text = "AI is thinking..."
        self.player_text = "Your turn!"

        self.start()

    def start(self):
        self.canvas = tk.Canvas(self.root, width=COLS * CELL_SIZE, height=ROWS * CELL_SIZE)
        self.canvas.pack()

        self.thinking_text = tk.Label(self.root, text="")
        self.thinking_text.pack()

        self.play_button = tk.Button(self.root, text="Play Game", command=self.play_game)
        self.play_button.pack(pady=10)

        self.quit_button = tk.Button(self.root, text="Quit", command=self.quit_game)
        self.quit_button.pack(pady=10)

    def play_game(self):
        self.canvas.config(bg="blue")
        self.play_button.forget()

        self.board = [[None for _ in range(COLS)] for _ in range(ROWS)]
        self.turn = "red"

        #TODO
        # start backend

        self.draw_board()

        self.ai_turn()

    def quit_game(self):
        self.root.destroy()

    def draw_board(self):
        self.canvas.delete("all")
        for row in range(ROWS):
            for col in range(COLS):
                x1 = col * CELL_SIZE
                y1 = row * CELL_SIZE
                x2 = x1 + CELL_SIZE
                y2 = y1 + CELL_SIZE
                self.canvas.create_oval(x1 + 5, y1 + 5, x2 - 5, y2 - 5, fill="white", outline="black")
                if self.board[row][col]:
                    self.canvas.create_oval(x1 + 5, y1 + 5, x2 - 5, y2 - 5, fill=self.board[row][col])

    def handle_click(self, event):
        col = event.x // CELL_SIZE
        self.make_mark(col)
        self.canvas.unbind("<Button-1>")
        self.ai_turn()

    def make_mark(self, col):
        row = self.get_available_row(col)
        if row is not None:
            self.board[row][col] = self.turn
            self.draw_board()
            #TODO
            if self.check_win(row, col):
                messagebox.showinfo("Game Over", f"{self.turn.capitalize()} wins!")
                self.canvas.unbind("<Button-1>")
            else:
                self.turn = "yellow" if self.turn == "red" else "red"

    def get_available_row(self, col):
        for row in reversed(range(ROWS)):
            if self.board[row][col] is None:
                return row
        return None

    def check_win(self, row, col):
        color = self.board[row][col]
        return (
            self.count_consecutive(row, col, 0, 1, color) + self.count_consecutive(row, col, 0, -1, color) > 2 or
            self.count_consecutive(row, col, 1, 0, color) + self.count_consecutive(row, col, -1, 0, color) > 2 or
            self.count_consecutive(row, col, 1, 1, color) + self.count_consecutive(row, col, -1, -1, color) > 2 or
            self.count_consecutive(row, col, 1, -1, color) + self.count_consecutive(row, col, -1, 1, color) > 2
        )

    def count_consecutive(self, row, col, delta_row, delta_col, color):
        count = 0
        r, c = row + delta_row, col + delta_col
        while 0 <= r < ROWS and 0 <= c < COLS and self.board[r][c] == color:
            count += 1
            r += delta_row
            c += delta_col
        return count

    def reset_game(self):
        self.board = [[None for _ in range(COLS)] for _ in range(ROWS)]
        self.turn = "red"
        self.draw_board()
        #TODO modify this
        self.canvas.bind("<Button-1>", self.handle_click)

    def player_turn(self):
        self.thinking_text.config(text=self.player_text)
        self.canvas.bind("<Button-1>", self.handle_click)

    def ai_turn(self):

        self.thinking_text.config(text=self.ai_text)
        self.root.update()

        #TODO
        # Reach out to backend for guess
        col = random.randint(0, 6)

        # Mark guess
        self.make_mark(col)
        self.player_turn()


    #TODO
    def end_game(self):
        pass




        

if __name__ == "__main__":
    root = tk.Tk()
    game = ConnectFour(root)
    root.mainloop()
