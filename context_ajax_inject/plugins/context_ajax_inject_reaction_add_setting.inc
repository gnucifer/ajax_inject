<?php
/**
 * Expose menu items as context reactions.
 */
class context_ajax_inject_reaction_add_setting extends context_reaction {
  /**
   * Provide a form element that allow the admin to chose a menu item.
	 */
	function options_form($context) {

		$values = $this->fetch_from_context($context);
		$options = drupal_map_assoc(array_keys(ajax_inject_contexts()));

		//Setting include home?
		$form['ajax_inject_contexts'] = array(
			'#title' => t('Ajax inject contexts'),
			'#required' => TRUE,
			'#type' => 'checkboxes',
			'#options' => $options,
			'#default_value' => isset($values['ajax_inject_contexts'])? $values['ajax_inject_contexts']: array(),
		);

		return $form;
  }

  /**
   * Override of options_form_submit().
   * Trim any identifier padding for non-unique path menu items.
   */
	function options_form_submit($values) {
    return $values;
  }

  /**
   * If primary + secondary links are pointed at the same menu, provide
   * contextual trailing by default.
	 */
	//TODO: is this really how it should be done? Seems inefficient since all plugins must run this iteration

	function execute() {
		$contexts = $this->get_contexts();
		foreach ($contexts as $context) {
			if (!empty($context->reactions[$this->plugin])) {
				$inject_contexts = isset($context->reactions[$this->plugin]['ajax_inject_contexts']) ? $context->reactions[$this->plugin]['ajax_inject_contexts'] : array();
				foreach($inject_contexts as $context_name) {
					ajax_inject_context_set_active($context_name);
				}
			}
    }
	}
}
