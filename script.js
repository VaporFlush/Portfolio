document.addEventListener('DOMContentLoaded', function() {
    // Get the About Me button and info box
    const aboutButton = document.querySelector('.about-button');
    const infoBox = document.querySelector('.info-box');

    // Function to toggle the info box
    function toggleInfoBox() {
        infoBox.style.display = infoBox.style.display === 'none' ? 'block' : 'none';
    }

    // Add event listener to the About Me button
    aboutButton.addEventListener('click', toggleInfoBox);

    // Get the close button inside the info box and add event listener
    const closeButton = document.querySelector('.close-button');
    closeButton.addEventListener('click', toggleInfoBox);

    // Get all project containers
    const projectContainers = document.querySelectorAll('.project-container');

    // Function to toggle project details pop-up visibility
    function toggleProjectPopup(projectDetails) {
        const projectPopup = document.getElementById('project-popup');
        const popupBody = projectPopup.querySelector('.popup-body');
        
        // Update popup content with project details
        popupBody.innerHTML = projectDetails.innerHTML;
        projectPopup.style.display = 'block';

        // Get the close button inside the project popup and add event listener
        const closeProjectDetailsButton = projectPopup.querySelector('.close-button');
        closeProjectDetailsButton.addEventListener('click', function() {
            projectPopup.style.display = 'none';
        });
    }

    // Add event listener to each project container
    projectContainers.forEach(function(container) {
        container.addEventListener('click', function() {
            const projectId = container.getAttribute('data-project-id');
            const projectDetails = document.getElementById(`project-details-${projectId}`);
            toggleProjectPopup(projectDetails);
        });
    });
});
