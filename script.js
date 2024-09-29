function loadContent(folderPath) {
    // Use AJAX to load content dynamically from the server
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        document.getElementById("content-area").innerHTML = this.responseText;
    }
    xhttp.open("GET", `loadContent.php?path=${folderPath}`, true);
    xhttp.send();
}
