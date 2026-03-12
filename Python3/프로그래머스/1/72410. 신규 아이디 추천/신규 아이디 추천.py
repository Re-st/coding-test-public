def solution(new_id):
    new_id = ''.join([i for i in new_id.lower() if i.isalpha() or i.isdigit() or i in {'-', '_', '.'}])
    while ".." in new_id:
        new_id = '.'.join(new_id.split(".."))
    new_id = new_id[1:] if new_id and new_id[0] == "." else new_id
    new_id = new_id[:-1] if new_id and new_id[-1] == "." else new_id
    new_id = "a" if not new_id else new_id
    new_id = new_id[:15]
    new_id = new_id[:-1] if new_id and new_id[-1] == "." else new_id
    while len(new_id) < 3:
        new_id += new_id[-1]
    return new_id