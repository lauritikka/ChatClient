const socket = new WebSocket('ws://192.168.0.12:6969');


function sendMessage() {
    // Get the value from the input field.
    var message = document.getElementById("text-field").value;
  
    // Clears the text-field after sending the message.
    document.getElementById("text-field").value = "";

    socket.send(message);
}


// Send message
socket.onmessage = function (message) {
    var messageContainer = document.getElementById("message-container");
    const newMessage = document.createElement('p');
    newMessage.textContent = message.data;
    messageContainer.appendChild(newMessage);
}

document.body.addEventListener('keydown', function(event) {
    if (event.key === 'Enter') {
        sendMessage();
    }
});