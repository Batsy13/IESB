import { jsonNoticiaRepository } from "@/repositories/json-noticia.repository";


export default async function Home() {

  const noticias = await jsonNoticiaRepository.findAll();

  return (
    <div className="grid grid-cols-1 gap-4 p-4">

      {noticias.map((noticia) => (
        <div key={noticia.titulo} className="p-4 flex flex-col gap-6 border border-[#FFF] rounded-[12px] shadow-xl">
          <div className="flex flex-col gap-4">
            <h1 className="text-red-500">{noticia.titulo}</h1>
            <h4>{noticia.subtitulo}</h4>
          </div>
          <p><strong>Autor:</strong> {noticia.autor}</p>
          <p>{noticia.texto}</p>
        </div>
      ))}

    </div>
  );
}
