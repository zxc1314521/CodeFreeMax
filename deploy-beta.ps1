$ErrorActionPreference = "Stop"

$BETA_IMAGE = "ssmdo/codefreemax:beta"

Write-Host "==> Pulling beta image: $BETA_IMAGE"
docker pull $BETA_IMAGE

Write-Host "==> Stopping current container..."
docker compose down

Write-Host "==> Starting with beta image..."
$env:DOCKER_IMAGE = $BETA_IMAGE
docker compose up -d --force-recreate --remove-orphans

Write-Host "==> Done! Current image:"
try {
    docker inspect --format='{{.Config.Image}}' codefreemax
} catch {
    Write-Host "(container not yet running)"
}
