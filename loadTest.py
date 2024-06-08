import json
import threading
from time import sleep
import requests
import random

urls = [('http://localhost:5000/', 100), 
        ('http://localhost:5000/aaa', 100), 
        ('http://localhost:5000/a.html', 100),
        ('http://localhost:5000/s.html', 100)]

def make_request(url, number_of_hits):
    for _ in range(int(number_of_hits)):
        try:
            requests.get(url, timeout=30)
        except requests.exceptions.RequestException as e:
            print(f"Request failed: {e}")
        # wait between 0.0001 and 0.1 s
        sleep(random.randrange(100, 1000) / 1000)

threads = []

NUMBER_OF_THREADS = 10
for (url, number_of_hits) in urls:
    for _ in range(NUMBER_OF_THREADS):
        thread = threading.Thread(target=make_request, args=(url, number_of_hits / NUMBER_OF_THREADS))
        threads.append(thread)
        thread.start()

for thread in threads:
    thread.join()

print("OK")
