use actix_files::Files;
use actix_web::{get, post, web, App, HttpResponse, HttpServer, Responder};
use serde::{Deserialize, Serialize};
use std::sync::{Arc, Mutex};

const HOST_FOR_SERVER: u16 = 11223;

#[derive(Debug, Serialize, Deserialize, Clone)]
struct SensorData {
    distance: f32,
    water: u32,
    temp: f32,
}

type SharedData = Arc<Mutex<Option<SensorData>>>;

#[post("/data")]
async fn post_data(data: web::Json<SensorData>, shared: web::Data<SharedData>) -> impl Responder {
    let mut sensor_data = shared.lock().unwrap();
    *sensor_data = Some(data.into_inner());
    HttpResponse::Ok()
}

#[get("/data")]
async fn get_data(shared: web::Data<SharedData>) -> impl Responder {
    let sensor_data = shared.lock().unwrap();
    if let Some(data) = &*sensor_data {
        HttpResponse::Ok().json(data)
    } else {
        HttpResponse::Ok().body("No data yet")
    }
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    let data = web::Data::new(Arc::new(Mutex::new(None::<SensorData>)));

    println!("Server running at http://localhost:{}", HOST_FOR_SERVER);
    HttpServer::new(move || {
        App::new()
            .app_data(data.clone())
            .service(post_data)
            .service(get_data)
            .service(Files::new("/", "./static").index_file("index.html"))
    })
    .bind(("0.0.0.0", HOST_FOR_SERVER))?
    .run()
    .await
}
