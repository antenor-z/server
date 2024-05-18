import json
import threading
from time import sleep
import requests
import random

urls = {'http://localhost:5000': 0, 
        'http://localhost:5000/aaa': 0, 
        'http://localhost:5000/a.html': 0,
        'http://localhost:5000/s.html': 0}

def make_request():
    try:
        url = random.choice(list(urls.keys()))
        requests.get(url, timeout=3)
        print(url)
        urls[url] += 1
    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}")

threads = []

for _ in range(100):
    for _ in range(15):
        thread = threading.Thread(target=make_request)
        threads.append(thread)
        thread.start()
    sleep(0.1)

for thread in threads:
    thread.join()

print(json.dumps(urls, indent=1))
print("OK")
