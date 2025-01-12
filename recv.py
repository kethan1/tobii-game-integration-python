import zmq
import signal

# Handle SIGINT to gracefully exit on Ctrl+C
signal.signal(signal.SIGINT, signal.SIG_DFL)

port = 5556

# Socket to talk to server
context = zmq.Context()
socket = context.socket(zmq.SUB)

print("Connecting...")
socket.connect(f"tcp://localhost:{port}")

# Subscribe to all topics (empty string means no filtering)
socket.setsockopt_string(zmq.SUBSCRIBE, "")

print("Listening...")

while True:
    message = socket.recv_string()
    print(message)
