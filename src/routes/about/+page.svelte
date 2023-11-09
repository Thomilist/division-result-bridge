<script lang="ts">
	import { title } from '$lib/stores';
    import { t } from 'svelte-intl-precompile';

    $title = `${$t("page.about.title")} - ${$t("project.name")}`;
</script>

<div class="narrow-content">
    <h1>
        {$t("page.about.title")}
    </h1>
    
    <p>
        {@html $t("page.about.icon-credit")}
    </p>
</div>