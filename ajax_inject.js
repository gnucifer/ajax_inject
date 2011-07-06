
Drupal.ajax_inject_context_data = {};

Drupal.behaviors.ajax_inject = function(context) {
	if(typeof(Drupal.settings.ajax_inject_contexts) != 'undefined') {
		//init group-by array
		var callback_data = {};
		for(callback_name in Drupal.settings.ajax_inject_callbacks) {
			callback_data[callback_name] = {};
		}
		for(context_name in Drupal.settings.ajax_inject_contexts) {
			//TODO: hmm, this?
			callback_data[Drupal.settings.ajax_inject_contexts[context_name].callback][context_name] =
				$.isFunction(Drupal.ajax_inject_context_data[context_name]) ? Drupal.ajax_inject_context_data[context_name].apply(this, [context]) : {};
		}

		for(callback_name in Drupal.settings.ajax_inject_callbacks) {
			//TODO: add option to skip on new ajax content, by not returning data aka undefined, for example, safe?
			if(typeof(callback_data[callback_name]) != 'undefined') {

				$.ajax({
						type : 'POST',
						url : Drupal.settings.ajax_inject_callbacks[callback_name],
						data : {'ajax_inject_contexts' : JSON.stringify(callback_data[callback_name])},
						success : function(data, textStatus) {
							console.dir(data);
							for(i in data) {
								var method = data[i].method || 'html';
								//TODO: check if function exists?
								$(data[i].selector, context)[method](data[i].html);
							}
						},
						dataType : 'json'
					});
			}
		}
	}
}
