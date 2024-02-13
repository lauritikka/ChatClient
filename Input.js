const socket = new WebSocket('ws://192.168.1.24:6969');
<<<<<<< HEAD

function getCookieJson(){
    return JSON.parse(document.cookie);
}
=======
>>>>>>> 925edab (Username, cookies and own message styling.)

function getCookieJson() {
    return JSON.parse(document.cookie);
}

function getMyUsername() {
    return getCookieJson()["username"];
}

// Read message from input
function readMessage() {
    var message = document.getElementById("text-field").value.trim();
    document.getElementById("text-field").value = "";

    console.log (message);
    
    var jsonData = {
        "username": getCookieJson()["username"],
        "userID": getCookieJson()["userID"],
        "message": message
    };

    if (message.length === 0){
        throw new Error("Message can't be empty");
    }

    return jsonData
}

// Send message to server 
function sendMessage() {
    try {
        var messageJson = readMessage();
        socket.send(JSON.stringify(messageJson));
    }
    catch (error) {
        alert(error.message);
    }
}

function handlePeerInfo(info) {

    var peers = info.peers;

    if (peers.length === 0) {
        return;
    }
}

function handleMessage(json) {
    var messageContainer = document.getElementById("message-container");

    var innerMessageContainer = document.createElement('div');
    innerMessageContainer.setAttribute('class', 'innerMessageContainer')

    var message = document.createElement('p');
    message.setAttribute("class", "message");

    var timestamp = document.createElement('p');
    timestamp.setAttribute("class", "timeStamp");

    const username = json["username"]; 
    const date = new Date(json.timeStamp);

    message.textContent = json.message;
    timestamp.textContent = ('0' + date.getHours()).slice(-2) + ":" + ('0' + date.getMinutes()).slice(-2);

    innerMessageContainer.appendChild(message);
    innerMessageContainer.appendChild(timestamp);
    if (username === getMyUsername()) {
        innerMessageContainer.style.marginLeft = 'auto';
        innerMessageContainer.style.marginRight = '30px';
    }
    messageContainer.appendChild(innerMessageContainer);

    messageContainer.scrollTop = messageContainer.scrollHeight;
}

function makeFakeMessage(fakeMsg) {
    var messageContainer = document.getElementById("message-container");

    var innerMessageContainer = document.createElement('div');
    innerMessageContainer.setAttribute('class', 'innerMessageContainer')

    var message = document.createElement('p');
    message.setAttribute("class", "message");

    var timestamp = document.createElement('p');
    timestamp.setAttribute("class", "timeStamp");

    const date = new Date();

    message.textContent = fakeMsg;
    timestamp.textContent = ('0' + date.getHours()).slice(-2) + ":" + ('0' + date.getMinutes()).slice(-2);

    innerMessageContainer.appendChild(message);
    innerMessageContainer.appendChild(timestamp);
    messageContainer.appendChild(innerMessageContainer);

    messageContainer.scrollTop = messageContainer.scrollHeight;
}

function caller() {
    const chatMessages = [
        "Hi there!",
        "How are you doing?",
        "What's up?",
        "I'm good, thanks for asking.",
        "Nice to meet you!",
        "How's the weather today?",
        "Did you hear about the latest news?",
        "I'm feeling a bit tired today.",
        "What's your favorite hobby?",
        "Any exciting plans for the weekend?",
        "I love chatting with new people!",
        "Tell me a fun fact about yourself.",
        "Have you watched any good movies lately?",
        "I can't believe it's already [current year]!",
        "Do you have any pets?",
        "What's your favorite food?",
        "I enjoy long walks and good conversations.",
        "Let's make today awesome!",
        "Coffee or tea?",
        "What's your favorite book?",
        "If you could travel anywhere, where would you go?",
        "I'm a big fan of [your favorite band/artist].",
        "What's the most interesting thing you've learned recently?",
      ];

    const randomMessage = chatMessages[Math.floor(Math.random() * chatMessages.length)];
      
    makeFakeMessage(randomMessage);
}

var intervalID = setInterval(caller, 2000);

// Handle received messages
socket.onmessage = function (event) {

    try {
        var json = JSON.parse(event.data);
        
        if ('peers' in json) {
            handlePeerInfo(json);
        }
        else {
            handleMessage(json);
        }

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