document.addEventListener('DOMContentLoaded', () => {
    let contact_form = document.querySelector('form');
    contact_form.addEventListener('submit', () => {
        let email = document.querySelector('#email').value;
        let why_contact = document.querySelector("#why_contact").value;
        sessionStorage.setItem('email', email);
        sessionStorage.setItem('why_contact', why_contact);
        document.querySelector('#email').value = '';
        document.querySelector('#why_contact').value = '';
        alert('Form has been successfully submitted');
    });
});