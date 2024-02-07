
function receiveMessage(message) {
    // Displaying the message.
    var chatContainer = document.getElementById("chat-container");
    var messageElement = document.createElement("div");
    messageElement.textContent = message;
    chatContainer.appendChild(messageElement);
}


