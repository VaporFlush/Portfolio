// Get the About Me button and info box
const aboutButton = document.querySelector('.about-button');
const infoBox = document.querySelector('.info-box');

// Function to toggle the info box
function toggleInfoBox() {
    infoBox.style.display = infoBox.style.display === 'none' ? 'block' : 'none';
}

// Add event listener to the About Me button
aboutButton.addEventListener('click', toggleInfoBox);

// Get the close button and add event listener
const closeButton = document.querySelector('.close-button');
closeButton.addEventListener('click', toggleInfoBox);

function toggleProjectDetails(projectId) {
    const projectDetails = document.getElementById(`project-details-${projectId}`);
    projectDetails.style.display = projectDetails.style.display === 'none' ? 'block' : 'none';
}
