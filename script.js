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
            projectDetails.style.display = projectDetails.style.display === 'none' ? 'block' : 'none';
        });
    });
});

// Function to toggle project details pop-up
document.addEventListener('DOMContentLoaded', function() {
    const projectButtons = document.querySelectorAll('.project-container');
    const projectPopups = document.querySelectorAll('.project-popup');
    
    projectButtons.forEach(function(button, index) {
        button.addEventListener('click', function() {
            projectPopups.forEach(function(popup) {
                popup.style.display = 'none';
            });
            
            const projectPopup = document.getElementById(`project-details-${index + 1}`);
            projectPopup.style.display = 'block';
        });
    });
});
