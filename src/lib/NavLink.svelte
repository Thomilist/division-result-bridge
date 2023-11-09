<script lang="ts">
    import { t } from 'svelte-intl-precompile';
	import { base } from "$app/paths";
	import type { NavLinkProps } from './types';

    export let props: NavLinkProps;
</script>

<a href="{base}{props.route}">{props.skip_translation ? props.label : $t(props.label)}</a>