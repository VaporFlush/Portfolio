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
    const popupWrapper = document.querySelector('.popup-wrapper');
    
    if (projectDetails.style.display === 'block') {
        projectDetails.style.display = 'none';
        popupWrapper.style.display = 'none';
    } else {
        // Hide all other project pop-ups
        const projectPopups = document.querySelectorAll('.project-popup');
        projectPopups.forEach(function(popup) {
            popup.style.display = 'none';
        });
        // Show the clicked project pop-up
        projectDetails.style.display = 'block';
        popupWrapper.style.display = 'flex'; // Show the wrapper
    }
}

document.body.addEventListener('wheel', function(event) {
    // Get all project containers
    const projectContainers = document.querySelectorAll('.project-container');
    
    // Find the currently visible project container
    let currentContainer = null;
    projectContainers.forEach(function(container) {
        const rect = container.getBoundingClientRect();
        if (rect.top >= 0 && rect.bottom <= window.innerHeight) {
            currentContainer = container;
        }
    });
    
    // If a project container is found and scrolling down
    if (currentContainer && event.deltaY > 0) {
        // Get the next sibling container
        const nextContainer = currentContainer.nextElementSibling;
        if (nextContainer) {
            // Scroll to the next container
            nextContainer.scrollIntoView({ behavior: 'smooth' });
        }
    }
    
    // If a project container is found and scrolling up
    if (currentContainer && event.deltaY < 0) {
        // Get the previous sibling container
        const prevContainer = currentContainer.previousElementSibling;
        if (prevContainer) {
            // Scroll to the previous container
            prevContainer.scrollIntoView({ behavior: 'smooth', block: 'end' });
        }
    }
});
