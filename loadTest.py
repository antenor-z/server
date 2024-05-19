import json
import threading
from time import sleep
import requests
import random

urls = [('http://localhost:5000', 27), 
        ('http://localhost:5000/aaa', 42), 
        ('http://localhost:5000/a.html', 59),
        ('http://localhost:5000/s.html', 19)]

def make_request(url, number_of_hits):
    for _ in range(int(number_of_hits)):
        try:
            requests.get(url, timeout=15)
        except requests.exceptions.RequestException as e:
            print(f"Request failed: {e}")
        # wait between 0.0001 and 0.1 s
        sleep(random.randrange(1, 100) / 1000)

threads = []

for (url, number_of_hits) in urls:
    thread = threading.Thread(target=make_request, args=(url, number_of_hits))
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print("OK")
