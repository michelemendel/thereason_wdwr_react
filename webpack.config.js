const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const outputDir = path.join(__dirname, 'build');
const isProd = process.env.NODE_ENV === 'production';

console.log("__dirname", __dirname)
console.log("outputDir", outputDir)

// const app = "react-test";
// const app = "notices";
// const app = "shirt-react";
// const app = "shirt-storage";
// const app = "router-basic";
// const app = "router-advanced";
const app = "router-component";

module.exports = {
    entry: "./apps/" + app + "/src/Index.bs.js",

    mode: isProd ? 'production' : 'development',

    output: {
        path: outputDir,
        filename: 'Index.js'
    },

    plugins: [
        new HtmlWebpackPlugin({
            template: path.join("apps", app, "src/index.html"),
            inject: false
        })
    ],

    module: {
        rules: [{
            test: /\.(png|jpg|svg)$/,
            use: [{
                loader: "file-loader",
                options: {
                    name: 'icons/[name].[ext]'
                }
            }]
        }]
    },

    devServer: {
        // compress: true,
        // contentBase: outputDir,
        port: process.env.PORT || 8000,
        historyApiFallback: true,
    }
};