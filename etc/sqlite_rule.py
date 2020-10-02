import sqlite3

def CREATE():
    conn = sqlite3.connect('rule.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS rules(returnCd INTEGER PRIMARY KEY, value TEXT)''')
    conn.commit()
    conn.close()

def INSERT(key,body):
    conn = sqlite3.connect('rule.db')
    c = conn.cursor()
    r = c.execute("INSERT INTO rules VALUES('1201','{1022}')")
    print(r)
    conn.commit()
    conn.close()

def DELETE(key):
    conn = sqlite3.connect('rule.db')
    c = conn.cursor()
    c.execute("")
    conn.commit()
    conn.close()

def READ(key):
    conn = sqlite3.connect('rule.db')
    c = conn.cursor()
    data = c.execute("SELECT * from rules")
    for e in data:
        print(e)
    conn.close()
    return data


if __name__ == "__main__":
    print('Input command')
    c = int(input())

    if c == 0:
        print('create table')
        CREATE()
    elif c == 1:
        print('insert')
        INSERT(0,0)
    elif c == 2:
        print('delete')
    elif c == 3:
        print('read')
        READ(0)
    elif c == 4:
        print('update')
    else:
        print('invalid input')
