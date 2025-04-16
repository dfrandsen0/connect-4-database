import tkinter as tk

import subprocess

ROWS = 6
COLS = 7
CELL_SIZE = 80

class ConnectFour:
    def __init__(self, root):
        self.root = root
        self.root.title("Connect Four")

        self.ai_text = "AI is thinking..."
        self.player_text = "Your turn!"

        self.server = subprocess.Popen(
            ['python', '.\\serverApp\\flaskServer.py']
        )
        self.backend = None

        self.start()

    def start(self):
        self.canvas = tk.Canvas(self.root, width=COLS * CELL_SIZE, height=ROWS * CELL_SIZE)
        # self.canvas.pack()

        self.thinking_text = tk.Label(self.root, text="")
        # self.thinking_text.pack()

        self.play_button = tk.Button(self.root, text="Play Game", command=self.play_game)
        self.play_button.pack(pady=10)

        self.quit_button = tk.Button(self.root, text="Quit", command=self.quit_game)
        self.quit_button.pack(pady=10)

        self.reset_button = tk.Button(self.root, text="Restart", command=self.reset_game)

        self.canvas.pack()

    def play_game(self):
        self.canvas.config(bg="blue")
        self.play_button.forget()

        self.quit_button.forget()
        self.canvas.pack()
        self.thinking_text.pack(pady=10)
        self.quit_button.pack(pady=5)

        self.board = [[None for _ in range(COLS)] for _ in range(ROWS)]
        self.turn = "red"

        self.start_backend()

        self.draw_board()
        self.ai_turn()

    def start_backend(self):
        self.backend = subprocess.Popen(
            # ['connect.exe', '0', '100', '1000000'],
            ['connect.exe', '0', '1', '1000'],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            text=True
        )

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
        self.canvas.unbind("<Button-1>")
        packet = str(col) + ' '
        self.backend.stdin.write(packet)
        self.backend.stdin.flush()
        if self.make_mark(col):
            self.ai_turn()

    def make_mark(self, col) -> bool:
        row = self.get_available_row(col)
        if row is not None:
            self.board[row][col] = self.turn
            self.draw_board()
            if self.check_win(row, col):
                self.end_game()
                return False
            else:
                self.turn = "yellow" if self.turn == "red" else "red"
                return True

    def end_game(self):
        self.canvas.unbind("<Button-1>")

        if(self.turn == "red"):
            self.thinking_text.config(text="The AI beat you!")
        else:
            self.thinking_text.config(text="You beat the AI!")
        
        self.play_button.forget()
        self.quit_button.forget()
        self.reset_button.pack(pady=10)
        self.quit_button.pack(pady=10)

        self.backend.wait()
        self.backend = None

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
        self.start_backend()
        self.ai_turn()

    def player_turn(self):
        self.thinking_text.config(text=self.player_text)
        self.canvas.bind("<Button-1>", self.handle_click)

    def ai_turn(self):

        self.thinking_text.config(text=self.ai_text)
        self.root.update()

        col = self.backend.stdout.read(1)

        col = ord(col) - ord('0')

        if self.make_mark(col):
            self.player_turn()
