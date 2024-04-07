fetch(`https://api.thingspeak.com/channels/2499645/feeds.json?api_key=3H9VZRPJENH9CPJX`)
.then(response => response.json())
.then(data => {
  document.getElementById('avg-light-intensity').textContent = data.field1;
  document.getElementById('rotation-angle').textContent = `Heading ${data.field2 == 0 ? "upward" : "downward"} with ${data.field2} degrees`;
  document.getElementById('sun-direction').textContent = `Direction of the Sun: ${data.field3}`;
})
.catch(error => console.error('Error:', error));


setInterval(() => {
  }, 15000);






