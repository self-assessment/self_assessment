<?php

class SelfAssessmentAdminImport {
    static function form($form, &$form_state) {
        $form['file'] = array(
            '#type' => 'file',
            '#title' => t('File'),
            '#description' => t("Self Assessment File (either JSON or XML)."),
        );

        $form['submit'] = [
            '#type' => 'submit',
            '#value' => t('Import Now'),
        ];

        return $form; // system_settings_form($form);
    }

    static function validate($form, &$form_state) {
        $file = file_save_upload(
            'file',
            [
                'file_validate_extensions' => ['xml json'],
                FILE_EXISTS_REPLACE
            ]
        );

        if ($file) {
            if ($file = file_move($file, 'public://')) {
                $form_state['values']['file'] = $file->fid;
                $form_state['storage']['file'] = $file;
            } else {
                form_set_error('file', t('Failed to write the uploaded file the site\'s file folder.'));
            }
        } else {
            form_set_error('file', t('No file was uploaded.'));
        }
    }

    static function submit($form, &$form_state) {
        if (empty($form_state['values']['file'])) {
            drupal_set_message(t('Please select a file'), 'error');
            return;
        }

        echo '<pre>'.htmlentities(print_r($form_state['values'], true)).'</pre>';

        die('SUBMITTED');
    }
}
