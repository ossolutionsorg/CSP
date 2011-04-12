<?php // $Id$

/**
 * @file
 * Rules actions for sending Mime-encoded emails (settings forms).
 */

/**
 * Action "Send an HTML mail to a user" configuration form.
 */
function mimemail_rules_action_mail_to_user_form($settings = array(), &$form) {
  $settings += array('from' => '', 'subject' => '', 'message' => '', 'message_html' => '', 'message_plaintext' => '', 'attachments' => '');
  $form['settings']['from'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender'),
    '#default_value' => $settings['from'],
    '#description' => t("The mail's from address. Leave it empty to use the site-wide configured address."),
  );
  $form['settings']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => $settings['subject'],
    '#description' => t("The mail's subject."),
  );
  $form['settings']['message_html'] = array(
    '#type' => 'textarea',
    '#title' => t('HTML message'),
    '#default_value' => $settings['message_html'],
    '#description' => t("The message body in HTML format."),
  );
  $form['settings']['message_plaintext'] = array(
    '#type' => 'textarea',
    '#title' => t('Text message'),
    '#default_value' => $settings['message_plaintext'],
    '#description' => t("Optional plaintext portion of a multipart e-mail."),
  );
  $form['settings']['attachments'] = array(
    '#type' => 'textarea',
    '#title' => t('Attachments'),
    '#default_value' => $settings['attachments'],
    '#description' => t('A list of attachments, one file per line. The format of each line is "[mimetype]:[path]", e.g. "image/png:/files/images/mypic.png"'),
  );
}

/**
 * Action "Send an HTML mail to an arbitrary mail address" configuration form.
 */
function mimemail_rules_action_mail_form($settings = array(), &$form) {
  $form['settings']['to'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient'),
    '#default_value' => isset($settings['to']) ? $settings['to'] : '',
    '#description' => t("The mail's recipient address. You may separate multiple addresses with ','."),
    '#required' => TRUE,
    '#weight' => -1,
  );
  $form['settings']['cc'] = array(
    '#type' => 'textfield',
    '#title' => t('CC Recipient'),
    '#default_value' => isset($settings['cc']) ? $settings['cc'] : '',
    '#description' => t("The mail's carbon copy address. You may separate multiple addresses with ','."),
    '#required' => FALSE,
    '#weight' => 0,
  );
  $form['settings']['bcc'] = array(
    '#type' => 'textfield',
    '#title' => t('BCC Recipient'),
    '#default_value' => isset($settings['bcc']) ? $settings['bcc'] : '',
    '#description' => t("The mail's blind carbon copy address. You may separate multiple addresses with ','."),
    '#required' => FALSE,
    '#weight' => 0,
  );
  mimemail_rules_action_mail_to_user_form($settings, $form);
}

/**
 * Action "Send an HTML mail to users of a role" configuration form.
 */
function mimemail_rules_action_mail_to_users_of_role_form($settings = array(), &$form) {
  // Select only non-anonymous user roles because anonymous users won't have emails.
  $roles = array_map('filter_xss_admin', user_roles(TRUE));
  $form['settings']['recipients'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Recipient roles'),
    '#prefix' => t('WARNING: This may cause problems if there are too many users of these roles on your site, as your server may not be able to handle all the mail requests all at once.'),
    '#required' => TRUE,
    '#default_value' => isset($settings['recipients']) ? $settings['recipients'] : array(),
    '#options' => $roles,
    '#description' => t('Select the roles whose users should receive this email.'),
  );
  mimemail_rules_action_mail_to_user_form($settings, $form);
}
