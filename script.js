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

document.addEventListener('DOMContentLoaded', function() {
    const projectContainers = document.querySelectorAll('.project-container');
    
    projectContainers.forEach(function(container) {
        container.addEventListener('click', function() {
            const projectId = container.getAttribute('data-project-id');
            const projectDetails = document.getElementById(`project-details-${projectId}`);
            toggleProjectPopup(projectDetails);
        });
    });
});

// Function to toggle project details pop-up visibility
function toggleProjectPopup(projectDetails) {
    if (projectDetails.style.display === 'block') {
        projectDetails.style.display = 'none';
    } else {
        // Hide all other project pop-ups
        const projectPopups = document.querySelectorAll('.project-popup');
        projectPopups.forEach(function(popup) {
            popup.style.display = 'none';
        });
        // Show the clicked project pop-up
        projectDetails.style.display = 'block';
    }
}
