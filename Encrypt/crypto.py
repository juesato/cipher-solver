import random
import sys
import argparse
NUMBER_LETTERS = 26
def transform_text(text, transform_map, remove_spaces=True):
    def transform_char(char, transform_map, remove_spaces):
        if char in transform_map:
            return transform_map[char]
        else:
            if (char == " " or char == "\n") and not remove_spaces:
                return " "
            else:
                return ""
    return "".join(transform_char(char,transform_map,remove_spaces) for char in text)

if __name__ == "__main__":
    letters = [chr(ord('a') + i) for i in range(NUMBER_LETTERS)]
    shuffled_letters = [chr(ord('a') + i) for i in range(NUMBER_LETTERS)]
    random.shuffle(shuffled_letters)
    transform_mapping = {orig_letter:transform_letter for orig_letter,transform_letter in zip(letters, shuffled_letters)}
    inverse_transform_mapping = {value:key for key,value in transform_mapping.items()}
    print(transform_mapping)
    parser = argparse.ArgumentParser(description="Randomly permute the text")
    parser.add_argument("-i","--input-file", dest="input_file", required=True,
                        help='Specify the input text')
    parser.add_argument("-o", "--output-file", required=True, dest="output_file", help="File to store the encrypted text")
    args = parser.parse_args()
    with open(args.input_file) as f:
        encrypted_text = transform_text(f.read().lower(), transform_mapping)
        original_text = transform_text(encrypted_text, inverse_transform_mapping)
        with open(args.output_file, "w") as g:
            g.write(encrypted_text)

