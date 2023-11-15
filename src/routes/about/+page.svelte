<script lang="ts">
	import { resources } from '$lib/resources';
	import { title } from '$lib/stores';
    import { t } from 'svelte-intl-precompile';

    $title = `${$t("page.about.title")} - ${$t("project.name")}`;
</script>

<div class="narrow-content">
    <h1>
        {$t("page.about.title")}
    </h1>
    
    <p>
        {@html $t("page.about.icon-credit", {values: 
        {
            icons_name: resources.external.bootstrap.project.icons.name,
            icons_link: resources.external.bootstrap.project.icons.route.website
        }})}
    </p>
</div>