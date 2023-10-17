import { addMessages, init } from 'svelte-intl-precompile';
import da from '$locales/da';
import en from '$locales/en';

export const prerender = true;

addMessages('da', da);
addMessages('en', en);

init({
    initialLocale: 'en',
    fallbackLocale: 'en'
});