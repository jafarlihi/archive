$('#uploadModal').on('shown.bs.modal', function() {
    $('#myInput').focus()
});

$(function() {
    $(document).on('change', ':file', function() {
        var input = $(this),
        numFiles = input.get(0).files ? input.get(0).files.length : 1,
        label = input.val().replace(/\\/g, '/').replace(/.*\//, '');
        input.trigger('fileselect', [numFiles, label]);
    });

    $(document).ready( function() {
        $(':file').on('fileselect', function(event, numFiles, label) {
            var input = $(this).parents('.input-group').find(':text'),
            log = numFiles > 1 ? numFiles + ' files selected' : label;

            if( input.length ) {
                input.val(log);
            } else {
                if(log) alert(log);
            }
        });
    });
});

$(window).load(function() {
    $('#galleryModal').modal('show');
});

$(window).load(function() {
    $('#albumModal').modal('show');
});

$(window).load(function() {
    $('#albumCreatorModal').modal('show');
});
