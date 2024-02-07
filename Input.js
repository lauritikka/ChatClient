const socket = new WebSocket('ws://192.168.0.12:6969');


function sendMessage() {
    var message = document.getElementById("text-field").value;
    console.log (message);
    document.getElementById("text-field").value = "";

    socket.send(message);
}


socket.onmessage = function (message) {
    var messageContainer = document.getElementById("message-container");
    const newMessage = document.createElement('p');
    newMessage.textContent = message.data;
    console.log (message.data);
    messageContainer.appendChild(newMessage);
    messageContainer.scrollTop = messageContainer.scrollHeight;
}

