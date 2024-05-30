<script lang="ts">
    import { fade } from "svelte/transition";
    export let titulo: string = "Operador";
    export let isOpen: boolean = false;

    export let color: "Rojo" | "Verde" | "Amarillo" = "Rojo";

    const styles = {
        Rojo: "background-color:red",
        Verde: "background-color:green",
        Amarillo: "background-color:yellow",
    };
</script>

<article>
    <h1 style="height: 36px;" id="rfid">{titulo}</h1>
    <div class="container">
        {#if !isOpen}
            <mark transition:fade />
        {/if}
        <span style={styles[color]} class={isOpen ? "open" : ""}></span>
        <div class="light" id="light"></div>
    </div>
</article>

<style>
    article {
        display: flex;
        justify-content: center;
        align-items: center;
        margin: 0;
        flex-direction: column;
        gap: 20px;
    }

    .container {
        text-align: center;
        position: relative;
        width: 220px;
        height: 200px;
    }

    mark {
        width: 100%;
        height: 100%;
        background-color: transparent;
        border-radius: 20px;
        position: absolute;
        top: 0;
        left: 0;
        z-index: 1;
        transition: all 1s;
    }

    span {
        width: 100px;
        height: 200px;
        background-color: brown;
        border: 2px solid #654321;
        border-radius: 5px;
        transition:
            transform 1s,
            left 1s;
        position: absolute;
        top: 0;
        left: 0;
        z-index: 2;
        filter: brightness(100%);
    }

    span.open {
        left: 120px;
        filter: brightness(60%);
    }

    .light {
        width: 20px;
        height: 20px;
        background-color: green;
        border-radius: 50%;
        position: absolute;
        top: -30px;
        left: 50%;
        transform: translateX(-50%);
        transition: background-color 1s;
    }

    span.open ~ .light {
        background-color: red;
    }
</style>
