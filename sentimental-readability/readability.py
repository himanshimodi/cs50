# TODO
# Readability
# Python
# Cmment for style


from cs50 import get_string


def main():
    # Get user input

    text = get_string("Text:")

    # print(count_words(text))
    word_number = count_words(text)
    L = (count_letters(text) * 100.0 / word_number)
    S = (count_sentences(text) * 100.0 / word_number)
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade:", index)


def count_letters(text):
    count = 0
    for i in text:
        if i.isalpha():
            count += 1
    return count


def count_words(text):
    count = 1
    for i in text:
        if (i == " "):
            count += 1
    return count


def count_sentences(text):
    count = 0
    sent_end = [".", "?", "!"]
    for i in text:
        if i in sent_end:
            count += 1
    return count


if __name__ == '__main__':
    main()