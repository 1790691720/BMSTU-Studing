from typing import List, Dict, Union


def find_author(library: List[Dict[str, Union[str, float]]], author: str) -> List:
    return [book for book in library if book['name'] == author]
#    res = []
#    for book in library:
#        if book['author'] == author:
#            res.append(book)
#    return res


def storage() -> List:
    return [
        {'author': '1', 'book-name': '11', 'price': 100},
        {'author': '1', 'book-name': '11', 'price': 100},
        {'author': '2', 'book-name': '22', 'price': 200},
        {'author': '3', 'book-name': '33', 'price': 300},
    ]


if __name__ == '__main__':
    books = storage()
    
    author = input('Name: ').strip()
    
    result = find_author(books, author)

    if result:
        for book in result:
            print('author: ', book)
    else:
        print('Empty')
