# Use the latest Alpine image as the base
FROM alpine:latest

# Set labels
LABEL maintainer="agiraude"
LABEL email="agiraude@student.42.fr"

# Install system dependencies
RUN apk update && \
  apk upgrade && \
  apk add --no-cache nodejs npm

# Create and set the working directory
WORKDIR /app

# Copy the Vue 3 client code to the working directory
COPY trsc-client/ .

# Install application dependencies
RUN npm install

# Build the Vue 3 client app for production
RUN npm run build && \
        npm install -g serve

# Expose port 5173 for the Vue 3 client app
EXPOSE 5173

# Set the entrypoint command to serve the built Vue 3 client app
CMD ["serve", "-s", "dist", "-l", "5173"]
# CMD [ "npm", "run", "dev" ]
