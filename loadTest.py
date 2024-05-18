import threading
import requests

url = 'http://localhost:5000'

def make_request():
    try:
        print("Requesting", url)
        response = requests.get(url)
        print(f"Response code: {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}")

threads = []

for _ in range(50):
    thread = threading.Thread(target=make_request)
    threads.append(thread)
    thread.start()

for thread in threads:
    thread.join()

print("Load test completed.")
