def getZarr(string, z):
    n = len(string)
    l, r, k = 0, 0, 0
    for i in range(1, n):
        if i > r:
            l, r = i, i
            while r < n and string[r - l] == string[r]:
                r += 1
            z[i] = r - l
            r -= 1
        else:
            k = i - l
            if z[k] < r - i + 1:
                z[i] = z[k]
            else:
                l = i
                while r < n and string[r - l] == string[r]:
                    r += 1
                z[i] = r - l
                r -= 1

def search(text, pattern):
    concat = pattern + "$" + text
    l = len(concat)
    z = [0] * l
    getZarr(concat, z)
    occurrences = []
    for i in range(l):
        if z[i] == len(pattern):
            occurrences.append(i - len(pattern) - 1)
    return occurrences

if __name__ == "__main__":
    # Read input from file
    with open("Python Input.txt", "r") as file:
        lines = file.readlines()
        if len(lines) < 2 or len(lines) % 2 != 0:
            print("Error: Input file must contain pairs of text and pattern.")
            exit(1)

        # Process each pair of lines (text and pattern)
        for i in range(0, len(lines), 2):
            text = lines[i].strip()
            pattern = lines[i + 1].strip()

            # Perform pattern search
            results = search(text, pattern)

            # Display results
            if results:
                print(f"Pattern '{pattern}' found at indices:", results)
            else:
                print(f"Pattern '{pattern}' not found in the text '{text}'.")
