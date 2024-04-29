document.addEventListener('DOMContentLoaded', function() {
    const projectContainers = document.querySelectorAll('.project-container');

    projectContainers.forEach(function(container) {
        container.addEventListener('click', function() {
            const projectId = container.getAttribute('data-project-id');
            const projectDetails = document.getElementById(`project-details-${projectId}`);
            toggleProjectPopup(projectDetails);
        });
    });

    // Event listener for About Me button
    const aboutButton = document.querySelector('.about-button');
    aboutButton.addEventListener('click', function() {
        const infoBox = document.querySelector('.info-box');
        infoBox.style.display = infoBox.style.display === 'none' ? 'block' : 'none';
    });

    // Event listener for close button in About Me pop-up
    const closeAboutButton = document.querySelector('.close-popup-button');
    closeAboutButton.addEventListener('click', function() {
        const infoBox = document.querySelector('.info-box');
        infoBox.style.display = 'none';
    });

    // Event listener for close button in project details pop-up
    const closePopupButton = document.querySelector('.close-project-details-button');
    closePopupButton.addEventListener('click', function() {
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
    projectPopup.style.display = 'block';
}
