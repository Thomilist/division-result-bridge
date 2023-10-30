import { addMessages, init } from 'svelte-intl-precompile';
import da from '$locales/da';
import en from '$locales/en';
import { default_locale, localeFromStore } from '$lib/localeHandler';
import { language } from '$lib/stores';
import { get } from 'svelte/store';

export const prerender = true;

addMessages("da", da);
addMessages("en", en);

init({
    initialLocale: localeFromStore(get(language)),
    fallbackLocale: default_locale
});