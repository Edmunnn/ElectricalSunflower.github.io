function fetchData() {
  fetch(`https://api.thingspeak.com/channels/2499645/feeds.json?api_key=3H9VZRPJENH9CPJX`)
  .then(response => response.json())
  .then(data => {
      const lastEntry = data.feeds[data.feeds.length - 1]; // Get the required last entry

      document.getElementById('avg-light-intensity').textContent = lastEntry.field1;
      document.getElementById('rotation-angle').textContent = `Heading ${lastEntry.field2 == 0 ? "upward" : "downward"} with ${lastEntry.field2} degrees`;

      
      const sunDirection = parseInt(lastEntry.field3, 10) >= 90 ? "North" : "South"; // create and display required texts
      document.getElementById('sun-direction').textContent = `Direction of the Sun: ${sunDirection}`; 

      document.getElementById('system-status').textContent = "The system is active."; // It tells the system is working which changing motor torque

      setTimeout(() => {
          document.getElementById('system-status').textContent = "The system is in a steady state."; // It tells the system is working with solar tracking staying at a position
      }, 5000); 
  })
  .catch(error => {
      console.error('Error:', error);
      document.getElementById('system-status').textContent = "The system is not working."; // It tells the system is not working
  });
}

fetchData();
setInterval(fetchData, 900000); //set up a time interval for the upadte of fetch data










