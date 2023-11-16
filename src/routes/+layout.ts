import { addMessages, init } from 'svelte-intl-precompile';
import da from '$locales/da';
import en from '$locales/en';
import { default_locale, localeFromStore } from '$lib/localeHandler';
import { language } from '$lib/stores';
import { get } from 'svelte/store';
import type { NavDropdownProps, NavHomeProps, NavItem } from '$lib/types';
import Logo from '$lib/icons/Logo.svelte';
import NavLink from '$lib/NavLink.svelte';
import LanguageSelect from '$lib/LanguageSelect.svelte';
import ThemeSwitch from '$lib/ThemeSwitch.svelte';
import { GearFill } from 'svelte-bootstrap-icons';
import type { LayoutLoad } from './$types';
import { resources } from '$lib/resources';

export const prerender = true;

addMessages("da", da);
addMessages("en", en);

init({
    initialLocale: localeFromStore(get(language)),
    fallbackLocale: default_locale
});

const home: NavHomeProps =
{
    label: resources.internal.home.label,
    route: resources.internal.home.route,
    icon:
    {
        component: Logo,
        size: 16
    }
};

const pages: NavItem[] =
[
    {component: NavLink, props: {label: resources.internal.download.label, route: resources.internal.download.route}},
    {component: NavLink, props: {label: resources.internal.docs.label, route: resources.internal.docs.route}}
];

const options: NavDropdownProps = 
{
    label: "options.name",
    align: "right",
    expand: "click",
    icon: GearFill,
    items:
    [
        {component: LanguageSelect, props: {label: "options.language.name"}},
        {component: ThemeSwitch, props: {label: "options.theme.name"}}
    ]
};

export const load: LayoutLoad = () =>
{
    return {
        nav:
        {
            home: home,
            items: pages,
            options: options
        }
    };
};