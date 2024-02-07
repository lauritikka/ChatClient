function sendMessage() {
    // Get the value from the input field.
    var message = document.getElementById("text-field").value;

    
    //send to server here, now console just logs.
    console.log("Message sent:", message);

     
    // Clears the text-field after sending the message.
    document.getElementById("text-field").value = "";
}