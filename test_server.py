import socket
import logging

# Set up logging
logging.basicConfig(filename='ping_pong_server.log', level=logging.INFO, 
                    format='%(asctime)s - %(message)s')

def log_message(message, addr):
    log_entry = f"Received '{message}' from {addr}"
    logging.info(log_entry)
    print(log_entry)

def ping_pong_server(host='192.168.149.132', port=8889):
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((host, port))
        print(f"Server listening on {host}:{port}")
        
        while True:
            data, addr = s.recvfrom(1024)
            message = data.decode()
            log_message(message, addr)
            if message == 'ping':
                print("Received 'ping', sending 'pong'")
                s.sendto(b'pong', addr)
            else:
                print(f"Received '{message}', sending 'Unknown command'")
                s.sendto(b'Unknown command', addr)

if __name__ == "__main__":
    ping_pong_server()
