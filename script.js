function fetchData() {
    fetch(`https://api.thingspeak.com/channels/2499645/feeds.json?api_key=3H9VZRPJENH9CPJX`)
    .then(response => response.json())
    .then(data => {
      // Display the data as before
      document.getElementById('avg-light-intensity').textContent = data.field1;
      document.getElementById('rotation-angle').textContent = `Heading ${data.field2 == 0 ? "upward" : "downward"} with ${data.field2} degrees`;
      document.getElementById('sun-direction').textContent = `Direction of the Sun: ${data.field3}`;

      // Update system status to "active" upon successful data retrieval
      document.getElementById('system-status').textContent = "The system is active.";

      // Set a timeout to change the status to "waiting" if no further data is fetched
      setTimeout(() => {
        document.getElementById('system-status').textContent = "The system is in a steady state.";
      }, 5000); // Switch to "steady" state after 5 seconds of inactivity

    })
    .catch(error => {
      console.error('Error:', error);
      document.getElementById('system-status').textContent = "The system is not working.";
    });
}

// Initial fetch
fetchData();

// Continuously update the fetch call every 15 minutes or as needed
setInterval(fetchData, 900000); // 15 minutes in milliseconds









