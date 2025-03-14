def format_text(input_text):
    """
    Formats the input text by adding curly braces at the start and end of each line,
    and commas after each digit.

    :param input_text: str, the input text to be formatted
    :return: str, the formatted text
    """
    formatted_lines = []
    for line in input_text.splitlines():
        formatted_line = "{" + ", ".join(line) + "},"
        formatted_lines.append(formatted_line)
    return "\n".join(formatted_lines)

# Örnek girdi
example_input = """000000000000
01111000000000"""

# Formattıng işlemini uygulama
formatted_text = format_text(example_input)
print(formatted_text)