const socket = new WebSocket('ws://192.168.0.12:6969');


// Read name and message from inputs
function readMessage() {
    var message = document.getElementById("text-field").value;
    document.getElementById("text-field").value = "";

    console.log (message);
    var name = document.getElementById("text-field2").value;

    var jsonData = {
        "name": name,
        "message": message
    };

    return jsonData
}

// Send message to server 
function sendMessage() {
    var messageJson = readMessage();
    socket.send(JSON.stringify(messageJson));
}

// Handle received messages
socket.onmessage = function (event) {

    try {
        var json = JSON.parse(event.data);

        var messageContainer = document.getElementById("message-container");

        var message = document.createElement('p');
        message.setAttribute("class", "message");

        var name = document.createElement('p');
        name.setAttribute("class", "name");

        name.textContent = json.name;
        message.textContent = json.message;

        messageContainer.appendChild(name);
        messageContainer.appendChild(message);

        messageContainer.scrollTop = messageContainer.scrollHeight;

    } catch(error) {
        console.error("Failed to parse message: ", error);
    }
}

// Send messages when user presses enter
document.body.addEventListener('keydown', function(event) {
    if (event.key === 'Enter') {
        sendMessage();
    }
});