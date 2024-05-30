<script lang="ts">
    import { io } from "socket.io-client";
    import { getToastStore, type ToastSettings } from "@skeletonlabs/skeleton";
    import Puerta from "../../components/Puerta.svelte";
    import type { Acceso } from "$lib/rfid";
    import Tabla from "../../components/Tabla.svelte";
    let socket = io("ws://localhost:3000");

    type dataTableRow = {
        position: number;
        nombre: string;
        nivel: number;
        fecha: string;
    };

    let rows: dataTableRow[] = [];

    const toastStore = getToastStore();
    let actual: (Acceso & { Pass: boolean }) | null = null;
    let open1 = true;
    let open2 = true;
    let open3 = true;
    socket.on("trusted", (msg: Acceso & { Pass: boolean }) => {
        handleOpenDoors(msg);
        if (!msg.Usuario) {
            const t: ToastSettings = {
                message: `Usuario no permitido`,
                timeout: 3500,
                background: "variant-filled-warning",
            };
            toastStore.trigger(t);
        } else {
            const fecha = new Date().toLocaleString("es-Mx", {
                day: "2-digit",
                month: "long",
                year: "numeric",
                hour12: true,
                hour: "2-digit",
                minute: "2-digit",
            });
            const t: ToastSettings = {
                message: `Usuario: ${msg.Usuario} | Nivel:${msg.Nivel} | Fecha: ${fecha}`,
                timeout: 3500,
            };
            toastStore.trigger(t);
        }
    });
    function handleOpenDoors(msg: Partial<Acceso & { Pass: boolean }>) {
        if (actual != null) return;
        if (!msg.Nivel) return;
        actual = msg as Acceso & { Pass: boolean };

        const fecha = new Date().toLocaleString("es-Mx", {
            day: "2-digit",
            month: "long",
            year: "numeric",
            hour12: true,
            hour: "2-digit",
            minute: "2-digit",
        });

        rows = [
            ...rows,
            {
                position: rows.length + 1,
                nombre: actual.Usuario as string,
                nivel: msg.Nivel,
                fecha,
            },
        ];

        if (msg.Nivel >= 1) open1 = false;
        setTimeout(() => (open1 = true), 1000);

        if (msg.Nivel >= 2) {
            setTimeout(() => (open2 = false), 1250);
            setTimeout(() => (open2 = true), 2250);
        }

        if (msg.Nivel >= 3) {
            setTimeout(() => (open3 = false), 2500);
            setTimeout(() => (open3 = true), 3500);
        }
        setTimeout(() => (actual = null), 4000);
    }
</script>

<div class="grid gap-5">
    <h4 class="text-9xl text-center border-b-8">GESTION DE ACCESOS</h4>
    <main class="flex justify-evenly">
        <Puerta color="Verde" isOpen={open1} />
        <Puerta color="Amarillo" isOpen={open2} titulo="Supervisor" />
        <Puerta isOpen={open3} titulo="Gerente" />
    </main>
</div>

<article class="w-[500px] h-48 absolute right-3 bottom-2 overflow-auto">
    <Tabla sourceData={rows} />
</article>
