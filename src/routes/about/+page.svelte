<script lang="ts">
    import { t } from 'svelte-intl-precompile';
</script>

<svelte:head>
    <title>
        {$t("page.about.title")} - {$t("project.name")}
    </title>
</svelte:head>

<div class="narrow-content">
    <h1>
        {$t("page.about.title")}
    </h1>
    
    <p>
        {@html $t("page.about.icon-credit")}
    </p>
</div>