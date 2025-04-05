def parse_results(file_path="results.txt"):
    counts = {'0': 0, '1': 0, '2': 0}
    total = 0

    with open(file_path, 'r') as f:
        for line in f:
            for char in line.strip():
                if char in counts:
                    counts[char] += 1
                    total += 1

    if total == 0:
        print("No data to process.")
        return

    for key in counts:
        percentage = (counts[key] / total) * 100
        print(f"{key}: {counts[key]} ({percentage:.2f}%)")

parse_results()
