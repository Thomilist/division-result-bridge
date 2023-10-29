<script lang="ts">
    import { t } from 'svelte-intl-precompile';
	import { base } from "$app/paths";

    export let props: NavLinkProps;
</script>

<a href="{base}{props.route}">{$t(props.label)}</a>