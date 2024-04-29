document.addEventListener('DOMContentLoaded', function() {
    const projectContainers = document.querySelectorAll('.project-container');

    projectContainers.forEach(function(container) {
        container.addEventListener('click', function() {
            const projectId = container.getAttribute('data-project-id');
            const projectDetails = document.getElementById(`project-details-${projectId}`);
            toggleProjectPopup(projectDetails);
        });
    });

    // Add event listener to close project popup button
    const closePopupButton = document.querySelector('.close-popup-button');
    closePopupButton.addEventListener('click', function() {
        const projectPopup = document.getElementById('project-popup');
        projectPopup.style.display = 'none';
    });

    // Add event listener to close button inside project details pop-up
    const closeProjectDetailsButton = document.querySelector('.close-project-details-button');
    closeProjectDetailsButton.addEventListener('click', function() {
        const projectPopup = document.getElementById('project-popup');
        projectPopup.style.display = 'none';
    });
});

// Function to toggle project details pop-up visibility
function toggleProjectPopup(projectDetails) {
    const projectPopup = document.getElementById('project-popup');
    const popupBody = projectPopup.querySelector('.popup-body');
    // Update popup content with project details
    popupBody.innerHTML = projectDetails.innerHTML;
    projectPopup.style.display = projectPopup.style.display === 'none' ? 'block' : 'none';
}
